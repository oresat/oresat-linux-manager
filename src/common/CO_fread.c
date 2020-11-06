/**
 * File transfer Object Dictionary Function.
 *
 * @file        CO_fread.c
 * @ingroup     file_transfer
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "CANopen.h"
#include "CO_driver.h"
#include "OD_helpers.h"
#include "log_message.h"
#include "CO_fread.h"
#include <dirent.h>
#include <libgen.h>
#include <linux/limits.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>


#ifndef CO_SDO_BUFFER_SIZE
/** The SDO buffer size. MUST BE <= 889 */
#define CO_SDO_BUFFER_SIZE  889
#endif

/** The size of the buffer for saving files */
#define FILE_BUFFER_SIZE    889
/** OD index for list of read files ODF */
#define FILELIST_ODF_INDEX  0x3002
/** OD index for reading files in the read list ODF */
#define FREAD_ODF_INDEX     0x3003
/** The length of the file list */
#define FILELIST_LEN        (UINT8_MAX-1)
/** The path to the cache we file are waiting */
#define FREAD_DIR           "/var/cache/candaemon/"


/** List of files ready for reading over CAN. */
static char *filelist[FILELIST_LEN] = {NULL};
/** The current file selected */
static uint8_t filelist_index = 0;
/** The file transfer ODF mutex */
static pthread_mutex_t fread_mtx;
/** Number of file existing FILELIST_LEN that aren't in filelist */
static int overflow = 0;
/** Files in cache */
static uint32_t total_files = 0;
/** Pointer to file being sent currently */
static FILE *fptr = NULL;
/** The progess of file transfer */
static uint32_t bytes_tansfered = 0;
/** The size of file the index points to */
static uint32_t filesize = 0;


static int filelist_init(void);
static int get_filesize(void);


int
CO_fread_setup(void) {

    pthread_mutex_lock(&fread_mtx);
    filelist_init();
    pthread_mutex_unlock(&fread_mtx);

    CO_OD_configure(CO->SDO[0], FILELIST_ODF_INDEX, fread_array_ODF, NULL, 0, 0U);
    CO_OD_configure(CO->SDO[0], FREAD_ODF_INDEX, fread_ODF, NULL, 0, 0U);

    return 0;
}


int
CO_fread_end(void) {
    int r = 0;

    if(fptr != NULL) {
        fclose(fptr);
        fptr = NULL;
    }

    // clean list
    for(uint8_t i=0; i<FILELIST_LEN; ++i) {
        if(filelist[i] == NULL)
            break; // No need to continue

        free(filelist[i]);
        filelist[i] = NULL;
    }

    return r;
}


CO_SDO_abortCode_t
fread_array_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;

    if(ODF_arg->reading == false)
        return CO_SDO_AB_READONLY; // can't write parameters, read only

    if(ODF_arg->subIndex == 0) {
        uint8_t temp = UINT8_MAX;
        ODF_arg->dataLength = sizeof(temp);
        memcpy(ODF_arg->data, &temp, ODF_arg->dataLength);
    }
    else if(ODF_arg->subIndex > 0) {
        pthread_mutex_lock(&fread_mtx);
        
        if(filelist[ODF_arg->subIndex] == NULL) { // No file
            char temp = '\0';
            ODF_arg->dataLength = 1;
            memcpy(ODF_arg->data, &temp, ODF_arg->dataLength);
        }
        else {
            ODF_arg->dataLength = strlen(filelist[ODF_arg->subIndex-1]) + 1;
            memcpy(ODF_arg->data, filelist[ODF_arg->subIndex-1], ODF_arg->dataLength);
        }
        
        pthread_mutex_unlock(&fread_mtx);
    }

    return ret;
}


CO_SDO_abortCode_t
fread_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    char filepath[] = FREAD_DIR;
    uint8_t subindices = FILELIST_LEN;
    uint32_t filesize = 0;
    uint8_t temp_uint8;

    switch(ODF_arg->subIndex) {
        case 0: // number of subindexes, uint8_t, readonly

            if(ODF_arg->reading == false)
                return CO_SDO_AB_READONLY;

            ODF_arg->dataLength = sizeof(subindices);
            memcpy(ODF_arg->data, &subindices, ODF_arg->dataLength);

            break;

        case 1: // filelist index selector, uint8_t, readwrite

            ODF_arg->dataLength = sizeof(temp_uint8);

            pthread_mutex_lock(&fread_mtx);

            if(ODF_arg->reading == true) {
                temp_uint8 = filelist_index+1; // add offset for subindex length
                memcpy(ODF_arg->data, &temp_uint8, ODF_arg->dataLength);
            }
            else {
                memcpy(&filelist_index, ODF_arg->data, ODF_arg->dataLength);
                --filelist_index; // remove offset for subindex length

                get_filesize();
            }
            
            pthread_mutex_unlock(&fread_mtx);

            break;

        case 2: // file name, domain, readonly

            if(ODF_arg->reading == false) {
                ret = CO_SDO_AB_READONLY;
                break;
            }

            pthread_mutex_lock(&fread_mtx);

            if(filelist[filelist_index] != NULL) { // no file
                ODF_arg->dataLength = strlen(filelist[filelist_index]+1);
                memcpy(ODF_arg->data, filelist[filelist_index],
                        ODF_arg->dataLength);
            }
            else { // file exist
                char temp = '\0';
                ODF_arg->dataLength = 1;
                memcpy(ODF_arg->data, &temp, ODF_arg->dataLength);
            }
            
            pthread_mutex_unlock(&fread_mtx);

            break;

        case 3: // file data, domain, readonly

            if(ODF_arg->reading == false) {
                ret = CO_SDO_AB_READONLY;
                break;
            }

            if(ODF_arg->firstSegment == true) { // 1st segment only
                //open file
                fptr = fopen(filelist[filelist_index], "r");
                if(fptr != NULL)
                    log_message(LOG_INFO, "Opened %s", filelist[filelist_index]);
                else {
                    log_message(LOG_ERR, "Failed to open %s", filelist[filelist_index]);
                    ret = CO_SDO_AB_GENERAL;
                    break;
                }

                ODF_arg->dataLengthTotal = filesize;
                bytes_tansfered = 0;
            }

            // read file
            if(fread(ODF_arg->data, ODF_arg->dataLength, 1, fptr) == 0) {
                log_message(LOG_ERR, "Failed to read to file %s", filepath);
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            bytes_tansfered += ODF_arg->dataLength;
        
            // Check if there are more segements comming
            if(bytes_tansfered > ODF_arg->dataLengthTotal) { // error
                log_message(LOG_ERR, "Sent more bytes than expected.");
                ret = CO_SDO_AB_GENERAL;
                break;
            }
            else if(bytes_tansfered == ODF_arg->dataLengthTotal) { // is complete
                if(fptr != NULL) {
                    log_message(LOG_INFO, "File %s closed", filepath);
                    fclose(fptr);
                    fptr = NULL;
                }
            }
            else // file transfer is on going
                ODF_arg->lastSegment = false;

            break;

        case 4: // file size, uint32_t, readonly

            if(ODF_arg->reading == false) {
                ret = CO_SDO_AB_READONLY;
                break;
            }

            pthread_mutex_lock(&fread_mtx);

            ODF_arg->dataLength = sizeof(filesize);
            memcpy(ODF_arg->data, &filesize, ODF_arg->dataLength);

            pthread_mutex_unlock(&fread_mtx);

            break;

        case 5: // delete current file, anything, writeonly

            if(ODF_arg->reading == true) {
                ret = CO_SDO_AB_WRITEONLY;
                break;
            }

            pthread_mutex_lock(&fread_mtx);

            if(filelist[filelist_index] != NULL) {
                strncat(filepath, filelist[filelist_index],
                        strlen(filelist[filelist_index])+1);

                // delete file and remove it from list
                remove(filepath);
                free(filelist[filelist_index]);
                filelist[filelist_index] = NULL;
                --total_files; 

                // remove the empty slot in the list 
                for(uint8_t i=filelist_index; i<FILELIST_LEN-1; ++i) {
                    if(filelist[i+1] == NULL)
                        break; // No need to continue looping

                    filelist[i] = filelist[i+1];
                    filelist[i+1] = NULL;
                }
            }

            pthread_mutex_unlock(&fread_mtx);

            break;

        case 6: // total # of files available, uint32_t, readonly

            if(ODF_arg->reading == false) {
                ret = CO_SDO_AB_READONLY;
                break;
            }

            pthread_mutex_lock(&fread_mtx);
            ODF_arg->dataLength = sizeof(total_files);
            memcpy(ODF_arg->data, &total_files, ODF_arg->dataLength);
            pthread_mutex_unlock(&fread_mtx);

            break;

        case 7: // # of files that overflowed aka not in filelist, uint32_t, readonly

            if(ODF_arg->reading == false) {
                ret = CO_SDO_AB_READONLY; 
                break;
            }
            pthread_mutex_lock(&fread_mtx);
            ODF_arg->dataLength = sizeof(overflow);
            memcpy(ODF_arg->data, &overflow, ODF_arg->dataLength);
            pthread_mutex_unlock(&fread_mtx);

            break;

        case 8: // refresh file array, anything, writeonly

            if(ODF_arg->reading == true) {
                ret = CO_SDO_AB_WRITEONLY;
                break;
            }

            pthread_mutex_lock(&fread_mtx);

            // clean list
            for(uint8_t i=0; i<FILELIST_LEN; ++i) {
                if(filelist[i] == NULL)
                    continue;

                free(filelist[i]);
                filelist[i] = NULL;
            }

            // rebuild list
            filelist_init();

            pthread_mutex_unlock(&fread_mtx);

            break;

        default:
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    return ret;
}

/**
 * Initialize filelist while file names from FREAD_DIR.
 * @return 0 on success and negative errno on errror.
 */
static int
filelist_init(void) {
    struct stat st = {0};
    struct dirent *dir;
    DIR *d;
    int r = 0;

    // zero static globals
    overflow = 0;
    total_files = 0;
    bytes_tansfered = 0;

    // make sure dir exist
    if(stat(FREAD_DIR, &st) == -1) {
        r = mkdir(FREAD_DIR, 0700);
        if(r != 0)
            log_message(LOG_ERR, "Failed to make "FREAD_DIR" directory with %d.", -r);
    }

    /* add all existing file to list */
    if((d = opendir(FREAD_DIR)) != NULL) {
        /* directory found */
        while((dir = readdir(d)) != NULL) {

            // skip . and ..
            if(strncmp(dir->d_name, ".", sizeof(dir->d_name)) ||
                    strncmp(dir->d_name, "..", sizeof(dir->d_name)))
                continue;

            if(total_files >= FILELIST_LEN) {
                filelist[total_files] = (char *)malloc(strlen(dir->d_name));
                strncpy(filelist[total_files], dir->d_name, strlen(dir->d_name));
            }
            else
                ++overflow;

            ++total_files;
        }
        closedir(d);
    }

    // set index back to zero
    filelist_index = 0;
    get_filesize();

    return r;
}


/**
 * A helper function to set the static global filesize variable. Should be
 * called under lock.
 * @return 0 on success and negative errno on errror.
 */
static int
get_filesize(void) {
    char filepath[PATH_MAX] = FREAD_DIR;
    int r = 0;
    filesize = 0; // set incase of error

    if(filelist[filelist_index] != NULL) {
        strncat(filepath, filelist[filelist_index],
                strlen(filelist[filelist_index])+1);

        if((fptr = fopen(filepath, "r")) != NULL) {
            fseek(fptr, 0, SEEK_END);
            filesize = ftell(fptr);
            fclose(fptr);
            fptr = NULL;
        }
        else
            r = -EIO;
    }

    return r;
}


int
app_send_file(char *filepath) {
    char new_filepath[PATH_MAX] = FREAD_DIR;
    char *filename;
    int r = 0;

    if(filepath == NULL || filepath[0] != '/')
        return -EINVAL;

    if((filename = basename(filepath)) == NULL)
        return -EINVAL;

    // make new filepath
    strncat(new_filepath, filename, strlen(filename)+1);

    // move file into read folder
    if(rename(filepath, new_filepath) == 0)
        return -EIO;

    pthread_mutex_lock(&fread_mtx);
   
    // append to filelist, if possible 
    if(total_files < FILELIST_LEN) {
        filelist[total_files] = (char *)malloc(strlen(filename)+1);
        strncpy(filelist[total_files], filename, strlen(filename)+1);
    }
    else 
        ++overflow;

    ++total_files;
    
    pthread_mutex_unlock(&fread_mtx);

    return r;
}


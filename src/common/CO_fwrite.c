/**
 * Receiving files ODF (Object Dictionary Function).
 *
 * @file        CO_fwrite.c
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
#include "CO_fwrite.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <linux/limits.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#ifndef FWRITE_ODF_INDEX
/** OD index for receive file ODF */
#define FWRITE_ODF_INDEX     0x3001
#endif

#ifndef FWRITE_DIR
/** 
 * The directory a received file will build in before moved to requested
 * directory.
 */
#define FWRITE_DIR           "/tmp/candaemon/"
#endif


/**
 * The internal data struct acting as a look up table on where to send files
 */
typedef struct {
    /** The name of app request the files with the key. */
    char *app_name;
    /** The key of request filenames */
    char *key;
    /** The absoulte path to the directory the file will be move to after file
     * transfer is complete.
     */
    char *send_dir;
    /**
     * Optioal callback function to call when a file is received. Usefull for
     * call dbus methods.
     */
    void (*cb_func)(const char *);
} fwrite_request_t;


/**
 * Delivers the file to where an app has defined. If no app register it, it
 * will be delete.
 * @return 0 on success or negative errno value on error.
 */
static int deliver_file(void);


/** The file pointer to current file being recv */
static FILE *fptr = NULL;
/** The progess of file transfer */
static uint32_t bytes_tansfered = 0;
/** The filepath of the file for fptr */
static char filepath[PATH_MAX];
/** The list of file key used a look up table when receiving files */
static fwrite_request_t *fkeys = NULL;
/** The lenght of the list for file keys */
static int fkeys_len = 0;
/** The file transfer ODF mutex */
static pthread_mutex_t fkeys_mutex;


int
CO_fwrite_setup(void) {
    struct stat st = {0};
    int r = 0;


    // make sure dir exist
    if(stat(FWRITE_DIR, &st) == -1)
        r = mkdir(FWRITE_DIR, 0700);

    CO_OD_configure(CO->SDO[0], FWRITE_ODF_INDEX, fwrite_ODF, NULL, 0, 0U);

    return r;
}


int
CO_fwrite_end(void) {
    if(fptr != NULL)
        fclose(fptr);

    if(fkeys != NULL) {
        for(unsigned int i=0; i<fkeys_len; ++i) {
            free(fkeys[i].app_name);
            free(fkeys[i].key);
            free(fkeys[i].send_dir);
        }

        free(fkeys);
    }

    return 0;
}


CO_SDO_abortCode_t
fwrite_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    uint8_t subindices = 4;

    /* error, no data to write */
    if(ODF_arg->dataLength == 0)
        return CO_SDO_AB_NO_DATA;

    if(ODF_arg->reading)
        return CO_SDO_AB_WRITEONLY; 

    switch(ODF_arg->subIndex) {
        case 0: // record size, uint8_t, readonly

            ODF_arg->dataLength = sizeof(subindices);
            memcpy(ODF_arg->data, &subindices, ODF_arg->dataLength);

            break;

        case 1: // file name, domain, writeonly

            if(ODF_arg->dataLengthTotal > (PATH_MAX-strlen(FWRITE_DIR))) {
                ret = CO_SDO_AB_OUT_OF_MEM;
                break;
            }
            
            if(ODF_arg->firstSegment) {
                // make filepath
                char temp[] = FWRITE_DIR;
                strncpy(filepath, temp, strlen(temp)+1);
                strncat(filepath, (char *)ODF_arg->data, ODF_arg->dataLength);

                bytes_tansfered = ODF_arg->dataLength;

                if(ODF_arg->dataLengthTotal > 889)
                    ODF_arg->lastSegment = false;
            }
            else {
                strncat(filepath, (char *)ODF_arg->data, ODF_arg->dataLength);
                bytes_tansfered += ODF_arg->dataLength;
            }

            if(bytes_tansfered >= ODF_arg->dataLengthTotal) {
                filepath[bytes_tansfered+strlen(FWRITE_DIR)] = '\0';
                log_message(LOG_ERR, "new file write %s", basename(filepath));
                ODF_arg->lastSegment = true;
            }

            break;

        case 2: // file data, domain, writeonly

            if(ODF_arg->firstSegment == true) { // 1st segment only
                //open file
                fptr = fopen(filepath, "w");
                if(fptr != NULL)
                    log_message(LOG_INFO, "Opened %s", filepath);
                else {
                    log_message(LOG_ERR, "Failed to open %s", filepath);
                    ret = CO_SDO_AB_GENERAL;
                    break;
                }

                bytes_tansfered = 0;
            }
            
            // write segment to file
            if(fwrite(ODF_arg->data, ODF_arg->dataLength, 1, fptr) == 0) {
                log_message(LOG_ERR, "Failed to write to file %s", filepath);
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            bytes_tansfered += ODF_arg->dataLength;
        
            // Check if there are more segements comming
            if(bytes_tansfered > ODF_arg->dataLengthTotal) { // error
                log_message(LOG_ERR, "Received more bytes than expected");
                ret = CO_SDO_AB_GENERAL;
                break;
            }
            else if(bytes_tansfered == ODF_arg->dataLengthTotal) { // is complete
                if(fptr != NULL) {
                    log_message(LOG_INFO, "File %s closed", filepath);
                    fclose(fptr);
                    fptr = NULL;
                }


                if(deliver_file() != 0) {
                    ret = CO_SDO_AB_GENERAL;
                    break;
                }

                filepath[0] = '\0';
                bytes_tansfered = 0;
                ODF_arg->lastSegment = true;
            }
            else // file transfer is ongoing
                ODF_arg->lastSegment = false;

            break;

        case 3: // cancel file transfer, domain, writeonly

            log_message(LOG_INFO, "Cancelling file write");

            if(fptr != NULL) {
                log_message(LOG_INFO, "File %s closed", filepath);
                fclose(fptr);
                fptr = NULL;
            }

            filepath[0] = '\0';
            bytes_tansfered = 0;
            ODF_arg->lastSegment = true;

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    if(ret != CO_SDO_AB_NONE) {
        log_message(LOG_ERR, "Wrting has errored, deleting file");

        if(fptr != NULL) {
            fclose(fptr);
            fptr = NULL;
        }

        remove(filepath);
        filepath[0] = '\0';
        bytes_tansfered = 0;
    }

    return ret;
}



static int
deliver_file(void) {
    char *filename = basename(filepath);
    char new_path[PATH_MAX], filename_key[PATH_MAX];
    int r = 0, end = 0;
    char *temp;
    bool key_found = false;

    if(fkeys == NULL) {
        log_message(LOG_INFO, "No keys requested, deleting %s", filepath);
        remove(filepath);
        return r; // no keys
    }

    if((temp = strchr(filename, '_')) == NULL) {
        log_message(LOG_INFO, "Filename %s is improperly formated", filename);
        return -1;
    }

    // find the next '_'
    for(unsigned int i=1; i<strlen(temp)-1; ++i) {
        if(temp[i] == '_') {
            end = i-1;
            break;
        }
    }

    if(end) { // a '_' was found, make substring
        strncpy(filename_key, &temp[1], end);
        filename_key[end] = '\0';
    }

    pthread_mutex_lock(&fkeys_mutex);

    for(unsigned int i=0; i<fkeys_len; ++i) {
        if(strncmp(fkeys[i].key, filename_key, strlen(filename_key)) == 0) {
            log_message(LOG_INFO, "file key \"%s\" found", filename_key);
            key_found = true; 

            // make paths
            strncpy(new_path, fkeys[i].send_dir, strlen(fkeys[i].send_dir)+1);
            strncat(new_path, filename, strlen(filename));

            // move file
            if((r = rename(filepath, new_path)) == 0)
                log_message(LOG_INFO, "File %s was move to %s", filename, fkeys[i].send_dir);
            else {
                log_message(LOG_ERR, "Failed to move %s to %s", filename, fkeys[i].send_dir);
                r = -r;
                break;
            }

            // call callback function
            if(fkeys[i].cb_func != NULL) {
                log_message(LOG_INFO, "Callback for %s was called", fkeys[i].app_name);
                fkeys[i].cb_func(filename);
            }

            break;
        }
    }

    if(key_found == false) {
        log_message(LOG_INFO, "\"%s\" was a invalid file key", filename_key);
        log_message(LOG_INFO, "deleting %s", filepath);
        remove(filepath);
    }

    pthread_mutex_unlock(&fkeys_mutex);

    return r;
}


int 
app_fwrite_request(
        char *app_name,
        char *key,
        char *send_dir,
        void (*cb_func)(const char *)
        ) {
    int app_name_len, key_len, send_dir_len;

    if(app_name == NULL || key == NULL || send_dir == NULL || send_dir[0] != '/')
        return -EINVAL;
    
    pthread_mutex_lock(&fkeys_mutex);

    if(fkeys == NULL) {
        fkeys_len = 1;
        fkeys = (fwrite_request_t *)malloc(sizeof(fwrite_request_t));
    }
    else {
        fkeys_len += 1;
        fkeys = (fwrite_request_t *)realloc(fkeys, sizeof(fwrite_request_t)*fkeys_len);
    }

    app_name_len = strlen(app_name) + 1;
    key_len = strlen(key) + 1;
    send_dir_len = strlen(send_dir) + 1;

    fkeys[fkeys_len-1].app_name = (char *)malloc(app_name_len);
    fkeys[fkeys_len-1].key = (char *)malloc(key_len);
    fkeys[fkeys_len-1].send_dir = (char *)malloc(send_dir_len);
    
    strncpy(fkeys[fkeys_len-1].app_name, app_name, app_name_len);
    strncpy(fkeys[fkeys_len-1].key, key, key_len);
    strncpy(fkeys[fkeys_len-1].send_dir, send_dir, send_dir_len);

    fkeys[fkeys_len-1].cb_func = cb_func;

    pthread_mutex_unlock(&fkeys_mutex);

    return 0;
}

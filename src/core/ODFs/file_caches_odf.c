/**
 * Reading/writing files over CAN ODF (Object Dictionary Function).
 *
 * @file        CO_file_transfer.c
 * @ingroup     file_transfer
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "CO_driver.h"
#include "CO_SDOserver.h"
#include "olm_file.h"
#include "olm_file_cache.h"
#include "utility.h"
#include "log_message.h"
#include "file_transfer_ODF.h"
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <linux/limits.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/syslog.h>
#include <sys/types.h>
#include <sys/stat.h>

// TODO move these to main
static file_transfer_t ft_odf_data = FILE_TRANSFER_INITIALIZER;
static struct olm_file_cache_t *fread_cache;
static struct olm_file_cache_t *fwrite_cache;

static int
ft_io_reset(file_io_t *data) {
    int r = 0;

    if (data == NULL)
        return -EINVAL;

    clear_dir(data->dir);

    if (data->fptr != NULL) {
        log_message(LOG_INFO, "%s has been closed", data->file);
        fclose(data->fptr);
        data->fptr = NULL;
    }

    if (data->file != NULL) {
        free(data->file);
        data->file = NULL;
    }

    data->bytes_transfered = 0;

    return r;
}

int
CO_file_transfer_init(void) {
    // make all the dirs TODO move to main
    mkdir_path(FREAD_CACHE_DIR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    mkdir_path(FWRITE_CACHE_DIR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    mkdir_path(FREAD_TMP_DIR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    mkdir_path(FWRITE_TMP_DIR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    // clean tmp dirs TODO move to main
    clear_dir(FREAD_TMP_DIR);
    clear_dir(FWRITE_TMP_DIR);

    // make cache objs TODO move to main
    olm_file_cache_new(FREAD_CACHE_DIR, &fread_cache);
    olm_file_cache_new(FWRITE_CACHE_DIR, &fwrite_cache);

    // configure ODFs
    CO_OD_configure(CO->SDO[0], OD_3001_fileCaches, file_caches_ODF, NULL, 0, 0U);
    CO_OD_configure(CO->SDO[0], OD_3002_fread, fread_ODF, NULL, 0, 0U);
    CO_OD_configure(CO->SDO[0], OD_3003_fwrite, fwrite_ODF, NULL, 0, 0U);

    return 0;
}

int
CO_file_transfer_end(void) {
    if (ft_odf_data.caches.keyword != NULL) {
        free(ft_odf_data.caches.keyword);
        ft_odf_data.caches.keyword = NULL;
    }

    ft_io_reset(&ft_odf_data.fread);
    ft_io_reset(&ft_odf_data.fwrite);

    // TODO move to main
    olm_file_cache_free(fread_cache);
    olm_file_cache_free(fwrite_cache);
    return 0;
}

CO_SDO_abortCode_t
file_caches_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    file_caches_t *caches  = &ft_odf_data.caches; // TODO add to ODF_arg->object

    switch(ODF_arg->subIndex) {

        case OD_3001_1_fileCaches_readCacheLen: // read cache len, uint32, readonly

            if (ODF_arg->reading)
                CO_setUint32(ODF_arg->data, fread_cache->len);
            else
                ret = CO_SDO_AB_READONLY;

            break;

        case OD_3001_2_fileCaches_writeCacheLen: // write cache len, uint32, readonly

            if (ODF_arg->reading)
                CO_setUint32(ODF_arg->data, fwrite_cache->len);
            else
                ret = CO_SDO_AB_READONLY;

            break;

        case OD_3001_3_fileCaches_selector: // cache selector, uint8, readwrite

            if (ODF_arg->reading) {
                CO_setUint8(ODF_arg->data, caches->selector);
            } else {
                uint8_t temp = CO_getUint8(ODF_arg->data);

                if (temp == READ_CACHE || temp == WRITE_CACHE)
                    caches->selector = temp;
                else 
                    return CO_SDO_AB_GENERAL; // invalid selector
            }
            
            break;

        case OD_3001_4_fileCaches_filter: // filter to apply to file list, domain, readwrite

            if (ODF_arg->reading) {
                if (caches->keyword == NULL) {
                    ret = CO_SDO_AB_NO_DATA;
                } else {
                    ODF_arg->dataLength = strlen(caches->keyword);
                    strncpy(ODF_arg->data, caches->keyword, ODF_arg->dataLength);
                }
            } else {
                if (caches->keyword != NULL) {
                    free(caches->keyword);
                    caches->keyword = NULL;
                }

                unsigned int len = ODF_arg->dataLength;

                // check if str end with '\0'
                if (ODF_arg->data[len-1] != '\0')
                    ++len; // add room for `\0`

                if ((caches->keyword = malloc(len)) == NULL)
                    ret = CO_SDO_AB_GENERAL;
                
                strncpy(caches->keyword, ODF_arg->data, ODF_arg->dataLength);

                if (len != ODF_arg->dataLength)
                    caches->keyword[ODF_arg->dataLength] = '\0'; // add missing '\0'
            }
            
            break;

        case OD_3001_5_fileCaches_readCacheFilterLen: // read cache len with filter applied, uint32, readonly

            if (ODF_arg->reading) {
                uint32_t len = olm_file_cache_len(fread_cache, caches->keyword);
                CO_setUint32(ODF_arg->data, len);
            } else {
                ret = CO_SDO_AB_READONLY;
            }

            break;

        case OD_3001_6_fileCaches_writeCacheFilterLen: // write cache len with filter applied, uint32, readonly

            if (ODF_arg->reading) {
                uint32_t len = olm_file_cache_len(fwrite_cache, caches->keyword);
                CO_setUint32(ODF_arg->data, len);
            } else {
                ret = CO_SDO_AB_READONLY;
            }

            break;

        case OD_3001_7_fileCaches_iterator: // filelist index selector, uint32, readwrite

            if (ODF_arg->reading) {
                CO_setUint32(ODF_arg->data, caches->iterator);
            } else {
                uint32_t iter = CO_getUint32(ODF_arg->data);
                olm_file_cache_t *cache;

                if (caches->selector == READ_CACHE)
                    cache = fread_cache;
                else
                    cache = fwrite_cache;

                if (iter < olm_file_cache_len(cache, caches->keyword))
                    caches->iterator = iter;
                else
                    ret = CO_SDO_AB_GENERAL; // invalid iterator value
            }
            
            break;

        case OD_3001_8_fileCaches_fileName: // file name, domain, readonly

            if (!ODF_arg->reading)
                return CO_SDO_AB_READONLY;

            olm_file_cache_t *cache;
            olm_file_t *file;

            if (caches->selector == READ_CACHE)
                cache = fread_cache;
            else
                cache = fwrite_cache;

            olm_file_cache_index(cache, caches->iterator, caches->keyword, &file);

            if (file != NULL && file.name != NULL) { // file exist
                ODF_arg->dataLength = strlen(file->name)+1;
                memcpy(ODF_arg->data, file.name, ODF_arg->dataLength);
            } else { // no file
                ret = CO_SDO_AB_NO_DATA;
            }

            break;

        case OD_3001_9_fileCaches_fileSize: // file size, uint32, readonly

            if (ODF_arg->reading)
                CO_setUint8(ODF_arg->data, &data.cache_selector);
            else
                data.cache_selector = CO_getUint8(ODF_arg->data);

            break;

        case OD_3001_10_fileCaches_remove: // delete current file, domain, writeonly

            if (ODF_arg->reading)
                return CO_SDO_AB_WRITEONLY;

            if (olm_file_cache_remove(fread_data->cache, fread_data->current_file->name) != 0)
                return CO_SDO_AB_GENERAL;

            data.current_index = 0;

            break;
    }

    return ret;
}

CO_SDO_abortCode_t
fread_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    char filepath[PATH_MAX] = "\0";
    file_io_t *fread = &ft_odf_data.fread;

    switch(ODF_arg->subIndex) {

        case OD_3002_1_fread_fileName: // file name, domain, readwrite

            if (ODF_arg->reading) {
                if (fread->file == NULL) {
                    ret = CO_SDO_AB_NO_DATA;
                } else {
                    ODF_arg->dataLength = strlen(fread->file)+1;
                    strncpy(ODF_arg->data, fread->file, ODF_arg->dataLength);
                }
            } else {
                char new_filepath[PATH_MAX];

                ft_io_reset(fread->file);

                strncpy(ODF_arg->data, filepath, ODF_arg->dataLength);

                // make sure string ends with '\0'
                if (filepath[ODF_arg->dataLength-1] != '\0')
                    filepath[ODF_arg->dataLength] = '\0';

                sprintf(new_filepath, "%s%s", FREAD_TMP_DIR, filepath);
                sprintf(filepath, "%s%s", FREAD_CACHE_DIR, filepath);
                
                // copy file from cache to tmp dir
                if (copyfile(new_filepath, filepath) != 0)
                    return CO_SDO_AB_GENERAL;

                // update filename
                size_t len = strlen(basename(new_filepath))+1;
                if ((fread->file = malloc(len)) == NULL)
                    return CO_SDO_AB_OUT_OF_MEM;
                strncpy(fread->file, basename(new_filepath), len);
            }

            break;

        case OD_3002_2_fread_fileData: // file data, domain, readonly

            if (ODF_arg->reading == false)
                return CO_SDO_AB_READONLY;

            if (ODF_arg->firstSegment == true) { // 1st segment only
                if (fread->file == NULL)
                    return CO_SDO_AB_NO_DATA;

                sprintf(filepath, "%s%s", FREAD_TMP_DIR, fread_file);
                bytes_transfered = 0;

                if ((fptr = fopen(filepath, "r")) != NULL) {
                    log_message(LOG_INFO, "Opened %s", filepath);
                } else {
                    log_message(LOG_ERR, "Failed to open %", filepath);
                    ret = CO_SDO_AB_GENERAL;
                    ft_io_reset(fread);
                    break;
                }
            }

            uint32_t bytes_left = ODF_arg->dataLengthTotal - bytes_transfered;

            // Check if there are more segements needed
            if (bytes_left > 889) { // more segements needed
                ODF_arg->dataLength = 889;
                ODF_arg->lastSegment = false;
            } else { // last segement
                ODF_arg->dataLength = bytes_left;
                ODF_arg->lastSegment = true;
            }

            // read file data
            if (fread(ODF_arg->data, 1, ODF_arg->dataLength, fptr) == 0) {
                log_message(LOG_ERR, "Failed to read to file %s", fread_file);
                ret = CO_SDO_AB_GENERAL;
                ft_io_reset(fread);
                break;
            }
        
            if (ODF_arg->lastSegment) { // fread is complete
                log_message(LOG_INFO, "%s has been closed", fread->file);
                fclose(fwrite->fptr);
                fwrite->fptr = NULL;
            } else { // fread is still in progress
                bytes_transfered += ODF_arg->dataLength;
            }

            break;

        case OD_3002_3_fread_reset: // reset fread, domain, writeonly
            
            if (ODF_arg->reading)
                ret = CO_SDO_AB_WRITEONLY;
            else
                ft_io_reset(fread);

            break;

        case OD_3002_4_fread_remove: // remove file from cache, domain, writeonly

            if (ODF_arg->reading) {
                ret = CO_SDO_AB_WRITEONLY;
            } else {
                olm_file_cache_remove(fread_cache, fread->file);
                ft_io_reset(fread);
            }

            break;
    }

    return ret;
}

CO_SDO_abortCode_t
fwrite_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    file_io_t *fwrite = &ft_odf_data.fwrite;
    char filepath[PATH_MAX];

    switch(ODF_arg->subIndex) {

        case OD_3003_1_fwrite_fileName: // file name, domain, readwrite

            if (ODF_arg->reading) {
                if (fwrite->file == NULL) {
                    ret = CO_SDO_AB_NO_DATA;
                } else {
                    ODF_arg->dataLength = strlen(fwrite->file)+1;
                    strncpy(fwrite->file, ODF_arg->data, ODF_arg->dataLength);
                }
            } else {
                ft_io_reset(fwrite->file);

                strncpy(ODF_arg->data, filepath, ODF_arg->dataLength);

                // make sure string ends with '\0'
                if (filepath[ODF_arg->dataLength-1] != '\0')
                    filepath[ODF_arg->dataLength] = '\0';

                size_t len = strlen(filepath)+1;
                if ((fwrite->file = malloc(len)) == NULL)
                    return CO_SDO_AB_OUT_OF_MEM;
                strncpy(fwrite->file, filepath, len);
            }

            break;

        case OD_3003_2_fwrite_fileData: // file data, domain, writeonly

            if (ODF_arg->reading)
                return CO_SDO_AB_WRITEONLY;

            if (ODF_arg->firstSegment == true) { // 1st segment only
                if (fwrite_file == NULL)
                    return CO_SDO_AB_NO_DATA;

                sprintf(filepath, "%s%s", FWRITE_TMP_DIR, fwrite->file);
                bytes_transfered = 0;

                if ((fptr = fopen(filepath, "w")) != NULL) {
                    log_message(LOG_INFO, "Opened %s", filepath);
                } else {
                    log_message(LOG_ERR, "Failed to open %s", filepath);
                    ret = CO_SDO_AB_GENERAL;
                    ft_io_reset(fwrite);
                    break;
                }
            }

            // Check if there are more segements needed
            if (ODF_arg->dataLengthTotal - bytes_transfered > 889)
                ODF_arg->lastSegment = false;
            else
                ODF_arg->lastSegment = true;

            // write file data
            if (fwrite(ODF_arg->data, 1, ODF_arg->dataLength, fptr) == 0) {
                log_message(LOG_ERR, "Failed to write to file %s", fwrite->file);
                ret = CO_SDO_AB_GENERAL;
                ft_io_reset(fwrite);
                break;
            }
        
            if (ODF_arg->lastSegment) { // fwrite is complete
                log_message(LOG_INFO, "%s has been closed", fwrite->file);
                fclose(fwrite->fptr);
                fwrite->fptr = NULL;

                olm_file_cache_add(fwrite_cache, fwrite->file);
                ft_io_reset(fwrite);
            } else { // fwrite is still in progress
                bytes_transfered += ODF_arg->dataLength;
            }

            break;

        case OD_3003_3_fwrite_reset: // reset fwrite, domain, writeonly
            
            if (ODF_arg->reading)
                ret = CO_SDO_AB_WRITEONLY;
            else
                ft_io_reset(fwrite);

            break;
    }

    return ret;
}

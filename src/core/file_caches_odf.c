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

#include "file_caches_odf.h"
#include "CANopen.h"
#include "logging.h"
#include "olm_file.h"
#include "olm_file_cache.h"
#include "utility.h"
#include <linux/limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
file_caches_free(file_caches_t *caches) {
    if (caches != NULL) {
        // these are handle elsewhere
        caches->fread_cache = NULL;
        caches->fwrite_cache = NULL;

        FREE_AND_NULL(caches->keyword);
    }
}

CO_SDO_abortCode_t
file_caches_ODF(CO_ODF_arg_t *ODF_arg) {
    file_caches_t *caches = (file_caches_t *)ODF_arg->object;
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    olm_file_cache_t *cache = NULL;
    olm_file_t *file = NULL;

    if (caches == NULL || caches->fread_cache == NULL
        || caches->fwrite_cache == NULL)
        return CO_SDO_AB_NO_DATA;

    if (OD_fileCaches.cacheSelector == FREAD_CACHE)
        cache = caches->fread_cache;
    else
        cache = caches->fwrite_cache;

    switch (ODF_arg->subIndex) {

    case OD_3002_1_fileCaches_freadCacheLen: // read cache len, uint8, readonly

        if (ODF_arg->reading) {
            if (caches->fread_cache->len < UINT8_MAX)
                CO_setUint8(ODF_arg->data, (uint8_t)caches->fread_cache->len);
            else
                CO_setUint8(ODF_arg->data, UINT8_MAX);
        } else {
            ret = CO_SDO_AB_READONLY;
        }

        break;

    case OD_3002_2_fileCaches_fwriteCacheLen: // write cache len, uint8,
                                              // readonly

        if (ODF_arg->reading) {
            if (caches->fwrite_cache->len < UINT8_MAX)
                CO_setUint8(ODF_arg->data, (uint8_t)caches->fwrite_cache->len);
            else
                CO_setUint8(ODF_arg->data, UINT8_MAX);
        } else {
            ret = CO_SDO_AB_READONLY;
        }

        break;

    case OD_3002_3_fileCaches_cacheSelector: // cache selector, uint8, readwrite

        if (!ODF_arg->reading) {
            uint8_t temp = CO_getUint8(ODF_arg->data);

            if (temp != FREAD_CACHE && temp != FWRITE_CACHE)
                return CO_SDO_AB_VALUE_HIGH; // invalid selector
        }

        break;

    case OD_3002_4_fileCaches_filter: // filter to apply to file list, domain,
                                      // readwrite

        if (ODF_arg->reading) {
            if (caches->keyword == NULL) {
                ret = CO_SDO_AB_NO_DATA;
            } else {
                ODF_arg->dataLength = strlen(caches->keyword) + 1;
                memcpy(ODF_arg->data, caches->keyword, ODF_arg->dataLength);
            }
        } else {
            if (caches->keyword != NULL) {
                free(caches->keyword);
                caches->keyword = NULL;
            }

            unsigned int len = ODF_arg->dataLength;

            if (len == 1 && ODF_arg->data[0] == 0)
                break; // only clearing keyword

            // check if str end with '\0'
            if (ODF_arg->data[len - 1] != '\0')
                ++len; // add room for `\0`

            if ((caches->keyword = malloc(len)) == NULL)
                ret = CO_SDO_AB_GENERAL;

            memcpy(caches->keyword, ODF_arg->data, ODF_arg->dataLength);

            if (len != ODF_arg->dataLength)
                caches->keyword[ODF_arg->dataLength] = '\0'; // add missing '\0'
        }

        break;

    case OD_3002_5_fileCaches_cacheLen: // cache len for selected cache and
                                        // filter, uint32, readonly

        if (ODF_arg->reading) {
            uint32_t len;

            if (OD_fileCaches.cacheSelector == FREAD_CACHE)
                len = olm_file_cache_len(caches->fread_cache, caches->keyword);
            else
                len = olm_file_cache_len(caches->fwrite_cache, caches->keyword);

            CO_setUint32(ODF_arg->data, len);
        } else {
            ret = CO_SDO_AB_READONLY;
        }

        break;

    case OD_3002_6_fileCaches_iterator: // filelist index selector, uint32,
                                        // readwrite

        if (!ODF_arg->reading) {
            if (CO_getUint32(ODF_arg->data)
                >= olm_file_cache_len(cache, caches->keyword))
                return CO_SDO_AB_VALUE_HIGH; // invalid iterator value
        }

        break;

    case OD_3002_7_fileCaches_fileName: // file name, domain, readonly

        if (!ODF_arg->reading)
            return CO_SDO_AB_READONLY;

        olm_file_cache_index(cache, OD_fileCaches.iterator, caches->keyword,
                             &file);
        if (file != NULL && file->name != NULL) { // file exist
            ODF_arg->dataLength = strlen(file->name) + 1;
            memcpy(ODF_arg->data, file->name, ODF_arg->dataLength);
        } else { // no file
            ret = CO_SDO_AB_NO_DATA;
        }

        break;

    case OD_3002_8_fileCaches_fileSize: // file size, uint32, readonly

        if (!ODF_arg->reading)
            return CO_SDO_AB_READONLY;

        olm_file_cache_index(cache, OD_fileCaches.iterator, caches->keyword,
                             &file);
        if (file != NULL) // file exist
            CO_setUint32(ODF_arg->data, file->size);
        else // no file
            ret = CO_SDO_AB_NO_DATA;

        break;

    case OD_3002_9_fileCaches_deleteFile: // delete current file, domain,
                                          // writeonly

        if (ODF_arg->reading)
            return CO_SDO_AB_WRITEONLY;

        olm_file_cache_index(cache, OD_fileCaches.iterator, caches->keyword,
                             &file);
        if (file != NULL) { // no file
            olm_file_cache_remove(cache, file->name);
            OD_fileCaches.iterator = 0;
        } else {
            ret = CO_SDO_AB_NO_DATA;
        }

        break;
    }

    if (file != NULL)
        olm_file_free(file);

    return ret;
}

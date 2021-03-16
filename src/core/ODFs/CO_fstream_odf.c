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

#include "CANopen.h"
#include "olm_file.h"
#include "olm_file_cache.h"
#include "utility.h"
#include "log_message.h"
#include "CO_fstream_odf.h"
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


#define SDO_BLOCK_LEN (127*7)

void
CO_fstream_reset(CO_fstream_t *data) {
    if (data == NULL) {
        clear_dir(data->dir);

        if (data->fptr != NULL) {
            log_message(LOG_INFO, "%s has been closed", data->file);
            fclose(data->fptr);
            data->fptr = NULL;
        }

        FREE_AND_NULL(data->file);

        data->bytes_transfered = 0;
    }
}

static CO_SDO_abortCode_t
CO_fstream_filename(CO_ODF_arg_t *ODF_arg, CO_fstream_t *fdata) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;

    if (ODF_arg->reading) {
        if (fdata->file == NULL) {
            ret = CO_SDO_AB_NO_DATA;
        } else {
            ODF_arg->dataLength = strlen(fdata->file)+1;
            memcpy(ODF_arg->data, fdata->file, ODF_arg->dataLength);
        }
    } else {
        char filename[SDO_BLOCK_LEN];

        if (ODF_arg->dataLengthTotal > SDO_BLOCK_LEN)
            return CO_SDO_AB_DATA_LONG;

        CO_fstream_reset(fdata);

        memcpy(ODF_arg->data, filename, ODF_arg->dataLength);

        // make sure string ends with '\0'
        if (filename[ODF_arg->dataLength-1] != '\0')
            filename[ODF_arg->dataLength] = '\0';

        // update filename
        size_t len = strlen(filename)+1;
        if ((fdata->file = malloc(len)) == NULL)
            return CO_SDO_AB_OUT_OF_MEM;
        strncpy(fdata->file, filename, len);
    }

    return ret;
}

CO_SDO_abortCode_t
CO_fread_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_fstream_t *fdata = (CO_fstream_t *)ODF_arg->object;
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;

    if (fdata == NULL)
        return CO_SDO_AB_DATA_LOC_CTRL;

    switch(ODF_arg->subIndex) {

        case OD_3002_1_fread_fileName: // file name, domain, readwrite

            ret = CO_fstream_filename(ODF_arg, fdata);

            // copy file from cache to tmp dir
            if (ret == CO_SDO_AB_NONE) { 
                char temp_filepath[PATH_MAX];
                char cache_filepath[PATH_MAX];

                sprintf(temp_filepath, "%s%s", fdata->dir, fdata->file);
                sprintf(cache_filepath, "%s%s", fdata->cache->dir, fdata->file);

                if (copyfile(temp_filepath, cache_filepath) != 0) {
                    CO_fstream_reset(fdata);
                    ret = CO_SDO_AB_DATA_LOC_CTRL;
                }
            }

            break;

        case OD_3002_2_fread_fileData: // file data, domain, readonly

            if (ODF_arg->reading == false)
                return CO_SDO_AB_READONLY;

            if (ODF_arg->firstSegment == true) { // 1st segment only
                char filepath[PATH_MAX] = "\0";

                if (fdata->file == NULL)
                    return CO_SDO_AB_NO_DATA;

                sprintf(filepath, "%s%s", fdata->dir, fdata->file);
                fdata->bytes_transfered = 0;

                if ((fdata->fptr = fopen(filepath, "r")) != NULL) {
                    log_message(LOG_INFO, "opened %s", filepath);
                } else {
                    log_message(LOG_ERR, "failed to open %", filepath);
                    CO_fstream_reset(fdata);
                    ret = CO_SDO_AB_DATA_LOC_CTRL;
                    break;
                }
            }

            // Check if there are more segements needed
            uint32_t bytes_left = ODF_arg->dataLengthTotal - fdata->bytes_transfered;
            if (bytes_left > SDO_BLOCK_LEN) { // more segements needed
                ODF_arg->dataLength = SDO_BLOCK_LEN;
                ODF_arg->lastSegment = false;
            } else { // last segement
                ODF_arg->dataLength = bytes_left;
                ODF_arg->lastSegment = true;
            }

            // read file data
            if (fread(ODF_arg->data, 1, ODF_arg->dataLength, fdata->fptr) == 0) {
                log_message(LOG_ERR, "Failed to read to file %s", fdata->file);
                CO_fstream_reset(fdata);
                ret = CO_SDO_AB_DATA_LOC_CTRL;
                break;
            }
        
            if (ODF_arg->lastSegment) {
                /* Do not call CO_fstream_reset() here as the CANopen Network
                 * Manager may want to use the OD_3002_4_fread_deleteFile sub
                 * index.
                 */
                log_message(LOG_INFO, "%s has been closed", fdata->file);
                fclose(fdata->fptr);
                fdata->fptr = NULL;
            } else {
                fdata->bytes_transfered += ODF_arg->dataLength;
            }

            break;

        case OD_3002_3_fread_reset: // reset fread, domain, writeonly
            
            if (ODF_arg->reading)
                ret = CO_SDO_AB_WRITEONLY;
            else
                CO_fstream_reset(fdata);

            break;

        case OD_3002_4_fread_deleteFile: // delete file from cache, domain, readonly

            if (ODF_arg->reading) {
                ret = CO_SDO_AB_WRITEONLY;
            } else {
                if (fdata->file == NULL)
                    return CO_SDO_AB_NO_DATA;

                if (olm_file_cache_remove(fdata->cache, fdata->file) != 0)
                    ret = CO_SDO_AB_DATA_LOC_CTRL;

                CO_fstream_reset(fdata);
            }

            break;
    }

    return ret;
}

CO_SDO_abortCode_t
CO_fwrite_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_fstream_t *fdata = (CO_fstream_t *)ODF_arg->object;
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;

    if (fdata == NULL)
        return CO_SDO_AB_DATA_LOC_CTRL;

    switch(ODF_arg->subIndex) {

        case OD_3003_1_fwrite_fileName: // file name, domain, readwrite

            ret = CO_fstream_filename(ODF_arg, fdata);

            break;

        case OD_3003_2_fwrite_fileData: // file data, domain, writeonly

            if (ODF_arg->reading)
                return CO_SDO_AB_WRITEONLY;

            if (ODF_arg->firstSegment == true) { // 1st segment only
                if (fdata->file == NULL)
                    return CO_SDO_AB_NO_DATA;

                char filepath[PATH_MAX];

                sprintf(filepath, "%s%s", fdata->dir, fdata->file);
                fdata->bytes_transfered = 0;

                if ((fdata->fptr = fopen(filepath, "w")) != NULL) {
                    log_message(LOG_INFO, "Opened %s", filepath);
                } else {
                    log_message(LOG_ERR, "Failed to open %s", filepath);
                    CO_fstream_reset(fdata);
                    ret = CO_SDO_AB_DATA_LOC_CTRL;
                    break;
                }
            }

            // Check if there are more segements needed
            if (ODF_arg->dataLengthTotal - fdata->bytes_transfered < SDO_BLOCK_LEN)
                ODF_arg->lastSegment = true;
            else
                ODF_arg->lastSegment = false;

            // write file data
            if (fwrite(ODF_arg->data, 1, ODF_arg->dataLength, fdata->fptr) == 0) {
                log_message(LOG_ERR, "Failed to write to file %s", fdata->file);
                CO_fstream_reset(fdata);
                ret = CO_SDO_AB_DATA_LOC_CTRL;
                break;
            }
        
            if (ODF_arg->lastSegment) {
                olm_file_cache_add(fdata->cache, fdata->file);
                CO_fstream_reset(fdata);
            } else {
                fdata->bytes_transfered += ODF_arg->dataLength;
            }

            break;

        case OD_3003_3_fwrite_reset: // reset fwrite, domain, writeonly
            
            if (ODF_arg->reading)
                ret = CO_SDO_AB_WRITEONLY;
            else
                CO_fstream_reset(fdata);

            break;
    }

    return ret;
}

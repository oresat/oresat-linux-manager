/**
 * OreSat Linux Updater dameon app.
 *
 * @file        updaterd_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "CANopen.h"
#include "logging.h"
#include "utility.h"
#include "olm_file_cache.h"
#include "updaterd.h"
#include "updater_app.h"
#include <linux/limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void
updater_async(void *data, olm_file_cache_t *fread_cache) {
    uint32_t temp_uint32;
    uint8_t temp_uint8;
    char *temp_str;

    if (updaterd_status(&temp_uint8) < 0) {
        CO_LOCK_OD();
        OD_updater.status = temp_uint8;
        CO_UNLOCK_OD();
    }

    if (updaterd_updates_available(&temp_uint32) < 0) {
        CO_LOCK_OD();
        if (temp_uint32 > UINT8_MAX)
            OD_updater.updatesAvailable = UINT8_MAX;
        else
            OD_updater.updatesAvailable = (uint8_t)temp_uint32;
        CO_UNLOCK_OD();
    }

    if (OD_updater.makeStatusFile) {
        if (updaterd_make_status_archive(&temp_str) >= 0)
            if (olm_file_cache_add(fread_cache, temp_str) < 0)
                log_printf(LOG_ERR, "failed to add %s to fread cache", temp_str);

        CO_LOCK_OD();
        OD_updater.makeStatusFile = false;
        CO_UNLOCK_OD();
    }

    if (OD_updater.update) {
        updaterd_update();

        CO_LOCK_OD();
        OD_updater.update = false;
        CO_UNLOCK_OD();
    }
}

CO_SDO_abortCode_t
updater_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    char *temp_str = (char *)ODF_arg->object;
    size_t len;

    if (ODF_arg->subIndex != OD_3100_3_updater_listUpdates) // list updates, domain, readonly
        return ret;

    if (!ODF_arg->reading)
        return CO_SDO_AB_READONLY;

    if (ODF_arg->firstSegment) {
        FREE_AND_NULL(temp_str);

        if (updaterd_list_updates(&temp_str) < 0)
            return CO_SDO_AB_NO_DATA;

        ODF_arg->dataLengthTotal = strlen(temp_str)+1;
        ODF_arg->offset = 0;
    }

    len = ODF_arg->dataLengthTotal - ODF_arg->offset;

    if (len < 889) {
        ODF_arg->dataLength = len;
        ODF_arg->lastSegment = true;
    } else {
        ODF_arg->dataLength = 899;
        ODF_arg->lastSegment = false;
    }
    
    ODF_arg->offset += ODF_arg->dataLength;
    memcpy(ODF_arg->data, temp_str, ODF_arg->dataLength);

    return ret;
}

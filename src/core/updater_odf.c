/**
 * OreSat Linux updater dameon app.
 *
 * @file        updater_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#include "CANopen.h"
#include "log_message.h"
#include "updater_app.h"
#include "updater_odf.h"
#include <linux/limits.h>
#include <stdint.h>
#include <stdlib.h>

CO_SDO_abortCode_t
updater_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    uint32_t temp_uint32;
    uint8_t temp_uint8;
    char *temp_str;

    switch(ODF_arg->subIndex) {
        case OD_3100_1_updater_status: // status,  uint8, readonly

            if(ODF_arg->reading) {
                if(updater_app_status(&temp_uint8) < 0)
                    ret = CO_SDO_AB_DATA_LOC_CTRL;
                else
                    CO_setUint8(ODF_arg->data, temp_uint8);
            } else {
                ret = CO_SDO_AB_READONLY;
            }
            break;

        case OD_3100_2_updater_updatesAvailable: // updates available,  uint8, readonly

            if(ODF_arg->reading) {
                if(updater_app_updates_available(&temp_uint32) < 0)
                    ret = CO_SDO_AB_DATA_LOC_CTRL;
                else
                    CO_setUint8(ODF_arg->data, (uint8_t)temp_uint32);
            } else {
                ret = CO_SDO_AB_READONLY;
            }
            break;

        case OD_3100_3_updater_listUpdates: // list updates,  domain, readonly

            if(ODF_arg->reading) {
                if(updater_app_list_updates(&temp_str) < 0) {
                    ret = CO_SDO_AB_DATA_LOC_CTRL;
                } else {
                    ODF_arg->dataLength = strlen(temp_str)+1 < 889 ? strlen(temp_str)+1 : 899;
                    memcpy(ODF_arg->data, temp_str, ODF_arg->dataLength);
                    free(temp_str);
                }
            } else {
                ret = CO_SDO_AB_READONLY;
            }
            break;

        case OD_3100_4_updater_update: // start update, uint8, writeonly

            if(ODF_arg->reading)
                ret = CO_SDO_AB_WRITEONLY;
            else 
                updater_app_update();
            break;

        case OD_3100_5_updater_makeStatusFile: // make status tar, uint8, writeonly

            if(ODF_arg->reading)
                ret = CO_SDO_AB_WRITEONLY;
            else
                updater_app_make_status_archive();
            break;
    }

    return ret;
}


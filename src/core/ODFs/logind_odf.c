/**
 * ODF for interfacing with systemd power setting.
 *
 * @file        logind_odf.c
 * @ingroup     core_odfs
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "CANopen.h"
#include "logind_odf.h"
#include "logind_app.h"

CO_SDO_abortCode_t
logind_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;

    if (ODF_arg->reading == true)
        return CO_SDO_AB_WRITEONLY;

    switch (ODF_arg->subIndex) {
        case 1: // reboot Linux system, uint8_t, writeonly

            if (logind_reboot() != 0)
                ret = CO_SDO_AB_GENERAL;

            break;

        case 2: // poweroff Linux system, uint8_t, readonly

            if (logind_poweroff() != 0)
                ret = CO_SDO_AB_GENERAL;

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    return ret;
}

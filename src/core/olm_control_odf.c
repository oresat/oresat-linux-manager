/**
 * OLM control ODF for reboot and poweroff commands.
 *
 * @file        olm_control_odf.c
 * @ingroup     olm_control_odf
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "CANopen.h"
#include "logind.h"

CO_SDO_abortCode_t
olm_control_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    int                r   = 0;

    switch (ODF_arg->subIndex) {
    case OD_3000_1_OLMControl_rebootBoard: // bash command, domain, readwrite

        if (ODF_arg->reading)
            return CO_SDO_AB_WRITEONLY;
        else
            r = logind_poweroff();

        break;

    case OD_3000_2_OLMControl_poweroffBoard: // poweroff, domain, writeonly

        if (ODF_arg->reading)
            return CO_SDO_AB_WRITEONLY;
        else
            r = logind_reboot();

        break;
    }

    if (r < 0)
        ret = CO_SDO_AB_GENERAL;

    return ret;
}

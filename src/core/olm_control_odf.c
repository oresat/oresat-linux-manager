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
#include "cpufreq.h"
#include "logind.h"

CO_SDO_abortCode_t
olm_control_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    int r = 0;

    switch (ODF_arg->subIndex) {
    case OD_3000_1_OLMControl_rebootBoard:

        if (!ODF_arg->reading && ODF_arg->data[0])
            r = logind_poweroff();

        break;

    case OD_3000_2_OLMControl_poweroffBoard:

        if (!ODF_arg->reading && ODF_arg->data[0])
            r = logind_reboot();

        break;
    }

    if (r < 0)
        ret = CO_SDO_AB_DATA_LOC_CTRL;

    return ret;
}

/**
 * App for interfacing with logind which has access to board power options.
 *
 * @file        logind_interface.c
 * @ingroup     logind_interface
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#include "app_include.h"
#include "logind_interface.h"
#include <systemd/sd-bus.h>


/** Dbus destionation for systemd power settings */
#define DESTINATION         "org.freedesktop.logind1"
/** Dbus interface name for systemd power settings */
#define INTERFACE_NAME      DESTINATION".Manager"
/** Dbus object name for systemd power settings */
#define OBJECT_PATH         "/org/freedesktop/logind1"

#ifndef LOGIND_ODF_INDEX
/** OD index for power management app ODF */
#define LOGIND_ODF_INDEX    0x3000
#endif

// logind OD subindices
#define LOGIND_SI_REBOOT    1
#define LOGIND_SI_POWEROFF  LOGIND_SI_REBOOT+1
#define LOGIND_I            LOGIND_SI_POWEROFF+1 // must be last


int
logind_app_setup() {
    app_OD_configure(LOGIND_ODF_INDEX, logind_ODF, NULL, 0, 0U);
    return 1;
}


CO_SDO_abortCode_t
logind_ODF(CO_ODF_arg_t *ODF_arg) { // TODO deal with huge performace requirements
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    sd_bus_error error = SD_BUS_ERROR_NULL;
    uint8_t subindices = LOGIND_I;
    int r;

    // can't read parameters, write only
    if (ODF_arg->reading == true) {
        return CO_SDO_AB_WRITEONLY;
    }

    switch (ODF_arg->subIndex) {
        case 0: // number of subindexes, uint8_t, readonly
            ODF_arg->dataLength = sizeof(subindices);
            memcpy(ODF_arg->data, &subindices, ODF_arg->dataLength);
            break;

        case LOGIND_SI_REBOOT: // reboot Linux system, uint8_t, writeonly
            r = sd_bus_call_method(
                    APP_DBUS.bus,
                    DESTINATION,
                    OBJECT_PATH,
                    INTERFACE_NAME,
                    "Reboot",
                    &error,
                    NULL,
                    NULL);
            if (r < 0) {
                log_message(LOG_ERR, "logind dbus method Reboot failed");
                ret = CO_SDO_AB_GENERAL;
            }

            break;

        case LOGIND_SI_POWEROFF: // poweroff Linux system, uint8_t, readonly
            r = sd_bus_call_method(
                    APP_DBUS.bus,
                    DESTINATION,
                    OBJECT_PATH,
                    INTERFACE_NAME,
                    "PowerOff",
                    &error,
                    NULL,
                    NULL);
            if (r < 0) {
                log_message(LOG_ERR, "logind dbus method Poweroff failed");
                ret = CO_SDO_AB_GENERAL;
            }

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    sd_bus_error_free(&error);
    return ret;
}



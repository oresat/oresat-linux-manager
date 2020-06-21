/**
 * App for interfacing with logind which has access to board power options.
 *
 * @file        logind_app.c
 * @ingroup     logind_app
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "app_OD_helpers.h"
#include "daemon_controller.h"
#include "dbus_controller.h"
#include "log_message.h"
#include "file_transfer.h"
#include "logind_app.h"
#include <systemd/sd-bus.h>


/** Dbus destionation for systemd power settings */
#define DESTINATION         "org.freedesktop.logind1"
/** Dbus interface name for systemd power settings */
#define INTERFACE_NAME      DESTINATION".Manager"
/** Dbus object name for systemd power settings */
#define OBJECT_PATH         "/org/freedesktop/logind1"
/** App's name */
#define APP_NAME            "Logind"
/** OD index for power management app ODF */
#define LOGIND_ODF_INDEX    0x3000


/**
 * Gobal for all apps to use to get acces to the CANdaemon dbus connetion.
 * Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;


int
logind_app_setup() {
    app_OD_configure(LOGIND_ODF_INDEX, logind_ODF, NULL, 0, 0U);
    return 1;
}


CO_SDO_abortCode_t
logind_ODF(CO_ODF_arg_t *ODF_arg) { // TODO deal with huge performace requerments
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    sd_bus_error error = SD_BUS_ERROR_NULL;
    int r;

    // can't read parameters, write only
    if (ODF_arg->reading == true) {
        return CO_SDO_AB_WRITEONLY;
    }

    switch (ODF_arg->subIndex) {
        case 1 : // reboot Linux system
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
                app_log_message(APP_NAME, LOG_ERR, "Method call Reboot failed");
                ret = CO_SDO_AB_GENERAL;
            }

            break;

        case 2 : // poweroff Linux system
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
                app_log_message(APP_NAME, LOG_ERR, "Method call PowerOff failed");
                ret = CO_SDO_AB_GENERAL;
            }

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    sd_bus_error_free(&error);
    return ret;
}



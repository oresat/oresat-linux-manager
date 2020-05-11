#include "log_message.h"
#include "app_OD_helpers.h"
#include "app_dbus_controller.h"
#include "file_transfer_ODF.h"
#include "power_management_app.h"
#include <systemd/sd-bus.h>


#define DESTINATION         "org.freedesktop.systemd1"
#define INTERFACE_NAME      DESTINATION".Manager"
#define OBJECT_PATH         "/org/freedesktop/systemd1"
#define APP_NAME            "Power Manager"


CO_SDO_abortCode_t
power_management_ODF(CO_ODF_arg_t *ODF_arg) { // TODO deal with huge performace requerments
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    sd_bus_error error = SD_BUS_ERROR_NULL;
    sd_bus *bus = NULL;
    int r;

    // can't read parameters, write only
    if (ODF_arg->reading == true) {
        return CO_SDO_AB_WRITEONLY;
    }

    // Connect to the bus
    if (sd_bus_open_system(&bus) < 0) {
        app_log_message(APP_NAME, LOG_CRIT, "Open system bus failed");
        return CO_SDO_AB_GENERAL;
    }

    switch (ODF_arg->subIndex) {
        case 1 : // reboot Linux system
            r = sd_bus_call_method(
                    bus,
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
                    bus,
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
    sd_bus_unref(bus);
    return ret;
}



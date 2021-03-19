/**
 * App for interfacing with logind which has access to board power options.
 *
 * @file        logind_app.c
 * @ingroup     logind_app
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "log_message.h"
#include "olm_app.h"
#include "app_manager.h"
#include "logind_app.h"
#include <systemd/sd-bus.h>

#define APP_NAME            "logind"
/** Dbus destionation for systemd power settings */
#define DESTINATION         "org.freedesktop.logind1"
/** Dbus interface name for systemd power settings */
#define INTERFACE_NAME      DESTINATION".Manager"
/** Dbus object name for systemd power settings */
#define OBJECT_PATH         "/org/freedesktop/logind1"

/**
 * Gobal for all apps to use to get access to the OLM's
 * D-Bus connections. Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;

// lazy way to deal with all the dbus arguments
#define DBUS_INFO APP_DBUS.bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

int
logind_reboot(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    int r;

    if ((r = sd_bus_call_method(DBUS_INFO, "Reboot", &err, NULL, NULL)) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "GetUnit", err.name);

    sd_bus_error_free(&err);
    return r;
}

int
logind_poweroff(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    int r;

    if ((r = sd_bus_call_method(DBUS_INFO, "PowerOff", &err, NULL, NULL)) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "GetUnit", err.name);

    sd_bus_error_free(&err);
    return r;
}

/**
 * Module for interfacing with Logind over D-Bus.
 *
 * @file        logind.c
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "logging.h"
#include "logind.h"
#include <systemd/sd-bus.h>

#define MODULE_NAME         "logind"
#define DESTINATION         "org.freedesktop.logind1"
#define INTERFACE_NAME      DESTINATION".Manager"
#define OBJECT_PATH         "/org/freedesktop/logind1"

/** System D-Bus connection. Defined in main.c */
extern sd_bus *system_bus;

// lazy way to deal with all the dbus arguments
#define DBUS_INFO system_bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

int
logind_reboot(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    int r;

    if ((r = sd_bus_call_method(DBUS_INFO, "Reboot", &err, NULL, NULL)) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_DEBUG, MODULE_NAME, "Reboot", err.name);

    sd_bus_error_free(&err);
    return r;
}

int
logind_poweroff(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    int r;

    if ((r = sd_bus_call_method(DBUS_INFO, "PowerOff", &err, NULL, NULL)) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_DEBUG, MODULE_NAME, "PowerOff", err.name);

    sd_bus_error_free(&err);
    return r;
}

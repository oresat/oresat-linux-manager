/**
 * Systemd app.
 *
 * @file        systemd_app.c
 * @ingroup     systemd_app
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "log_message.h"
#include "olm_app.h"
#include "utility.h"
#include "dbus_controller.h"
#include "systemd_app.h"
#include <systemd/sd-bus.h>

/** App's name */
#define APP_NAME        "Systemd"
/** Dbus destionation for systemd */
#define DESTINATION     "org.freedesktop.systemd1"
/** Dbus interface name for systemd */
#define INTERFACE_NAME  DESTINATION
/** Dbus object path for systemd */
#define OBJECT_PATH     "/org.freedesktop/systemd1"

/**
 * Gobal for all apps to use to get access to the OLM's
 * D-Bus connections. Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;

int
start_daemon(char *daemon_name) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r;

    r = sd_bus_call_method(
            APP_DBUS.bus,
            DESTINATION,
            OBJECT_PATH,
            INTERFACE_NAME,
            "StartUnit",
            &err,
            &mess,
            "ss",
            daemon_name,
            "fail");
    if (r < 0)
        log_message(LOG_ERR, "systemd method call StartUnit failed for %s", daemon_name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
stop_daemon(char *daemon_name) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r;

    r = sd_bus_call_method(
            APP_DBUS.bus,
            DESTINATION,
            OBJECT_PATH,
            INTERFACE_NAME,
            "StopUnit",
            &err,
            &mess,
            "ss",
            daemon_name,
            "fail");
    if (r < 0)
        log_message(LOG_ERR, "systemd method call StopUnit failed for %s", daemon_name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
restart_daemon(char *daemon_name) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r;

    r = sd_bus_call_method(
            APP_DBUS.bus,
            DESTINATION,
            OBJECT_PATH,
            INTERFACE_NAME,
            "RestartUnit",
            &err,
            &mess,
            "ss",
            daemon_name,
            "fail");
    if (r < 0)
        log_message(LOG_ERR, "systemd method call RestartUnit failed for %s", daemon_name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

/**
 * Systemd app for CANdaemon, that allow it to control daemons using dbus.
 *
 * @file        systemd_app.c
 * @ingroup     systemd_app
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */



#include "app_include.h"
#include "systemd_app.h"
#include <systemd/sd-bus.h>


/** App's name */
#define APP_NAME                        "Systemd"
/** Dbus destionation for systemd */
#define DESTINATION                     "org.freedesktop.systemd1"
/** Dbus interface name for systemd */
#define INTERFACE_NAME                  DESTINATION
/** Dbus object path for systemd */
#define OBJECT_PATH                     "/org.freedesktop/systemd1"


/**
 * Gobal for all apps to use to get acces to the CANdaemon dbus connetion.
 * Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;


int
systemd_app_setup() {
    return 1;
}


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
        app_log_message(APP_NAME, LOG_ERR, "Method call StartUnit failed");

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
        app_log_message(APP_NAME, LOG_ERR, "Method call StopUnit failed");

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
        app_log_message(APP_NAME, LOG_ERR, "Method call RestarttUnit failed");

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

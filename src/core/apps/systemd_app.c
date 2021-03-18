/**
 * The app for interfacing with systemd over D-Bus.
 *
 * @file        systemd_app.c
 * @ingroup     core_apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "log_message.h"
#include "utility.h"
#include "app_manager.h"
#include "systemd_app.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <systemd/sd-bus.h>

/** App's name */
#define APP_NAME            "Systemd"
/** Systemd D-Bus destionation */
#define DESTINATION         "org.freedesktop.systemd1"
/** Systemd Manager D-Bus interface for systemd */
#define MANAGER_INTERFACE   DESTINATION".Manager"
/** Systemd Unit D-Bus interface. */
#define UNIT_INTERFACE      DESTINATION".Unit"
/** Systmed D-Bus object path. */
#define OBJECT_PATH         "/org/freedesktop/systemd1"

/**
 * Gobal for all apps to use to get access to the OLM's
 * D-Bus connections. Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;

const char *active_state_str[] = {
    "active",
    "reloading",
    "inactive",
    "failed",
    "activating",
    "deactivating",
};

char *
get_unit(const char *name) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    char *r = NULL, *unit = NULL;

    if (unit == NULL)
        return r;
    
    if (sd_bus_call_method(APP_DBUS.bus, DESTINATION, OBJECT_PATH, \
                MANAGER_INTERFACE, "GetUnit", &err, &mess, "s", name) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "GetUnit", err);
    else if (sd_bus_message_read(mess, "o", &unit) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, APP_NAME, "GetUnit", err);
    else
        if ((r = malloc(strlen(unit)+1)) != NULL)  // must copy strings
            strncpy(r, unit, strlen(unit)+1);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
start_unit(const char *unit) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r;

    if (unit == NULL)
        return -EINVAL;
    
    if ((r = sd_bus_call_method(APP_DBUS.bus, DESTINATION, unit, \
                UNIT_INTERFACE, "StartUnit", &err, &mess, "s", "fail")) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "StartUnit", err);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}


int
stop_unit(const char *unit) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r;

    if (unit == NULL)
        return -EINVAL;
    
    if ((r = sd_bus_call_method(APP_DBUS.bus, DESTINATION, unit, \
                UNIT_INTERFACE, "StopUnit", &err, &mess, "s", "fail")) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "StoptUnit", err);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
restart_unit(const char *unit) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r;

    if (unit == NULL)
        return -EINVAL;
    
    if ((r = sd_bus_call_method(APP_DBUS.bus, DESTINATION, unit, \
                UNIT_INTERFACE, "RestartUnit", &err, &mess, "s", "fail")) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "RestartUnit", err);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
get_active_state_unit(const char *unit) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    char *state;
    int r = -1;

    if (unit == NULL)
        return -EINVAL;

    if (sd_bus_get_property(APP_DBUS.bus, DESTINATION, unit, UNIT_INTERFACE, \
                "ActiveState", &err, &mess, "d") < 0)
        LOG_DBUS_GET_PROPERTY_ERROR(LOG_ERR, APP_NAME, "ActiveState", err);
    else if (sd_bus_message_read(mess, "s", &state) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, APP_NAME, "ActiveState", err);
    else 
        for (int i=0; i<sizeof(active_state_str); ++i)
            if (strncmp(state, active_state_str[i], strlen(state)+1) == 0) {
                r = i;
                break;
            }

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

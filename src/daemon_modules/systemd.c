/**
 * Module for interfacing with Systemd over D-Bus.
 *
 * @file        systemd.c
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "logging.h"
#include "utility.h"
#include "olm_app.h"
#include "systemd.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <systemd/sd-bus.h>

#define MODULE_NAME         "Systemd"
#define DESTINATION         "org.freedesktop.systemd1"
#define MANAGER_INTERFACE   DESTINATION".Manager"
#define UNIT_INTERFACE      DESTINATION".Unit"
#define OBJECT_PATH         "/org/freedesktop/systemd1"

/** System D-Bus connection. Defined in main.c */
extern sd_bus *system_bus;

static const char *active_state_str[] = {
    "inactive",
    "reloading",
    "active",
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
    
    if (sd_bus_call_method(system_bus, DESTINATION, OBJECT_PATH, \
                MANAGER_INTERFACE, "GetUnit", &err, &mess, "s", name) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, MODULE_NAME, "GetUnit", err.name);
    else if (sd_bus_message_read(mess, "o", &unit) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, MODULE_NAME, "GetUnit", err.name);
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
    
    if ((r = sd_bus_call_method(system_bus, DESTINATION, unit, \
                UNIT_INTERFACE, "StartUnit", &err, &mess, "s", "fail")) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, MODULE_NAME, "StartUnit", err.name);

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
    
    if ((r = sd_bus_call_method(system_bus, DESTINATION, unit, \
                UNIT_INTERFACE, "StopUnit", &err, &mess, "s", "fail")) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, MODULE_NAME, "StoptUnit", err.name);

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
    
    if ((r = sd_bus_call_method(system_bus, DESTINATION, unit, \
                UNIT_INTERFACE, "RestartUnit", &err, &mess, "s", "fail")) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, MODULE_NAME, "RestartUnit", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

unit_active_states_t
get_active_state_unit(const char *unit) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    char *state;
    int r = UNIT_UNKNOWN;

    if (unit == NULL)
        return r;

    if (sd_bus_get_property(system_bus, DESTINATION, unit, UNIT_INTERFACE, \
                "ActiveState", &err, &mess, "d") < 0) {
        LOG_DBUS_GET_PROPERTY_ERROR(LOG_ERR, MODULE_NAME, "ActiveState", err.name);
    } else if (sd_bus_message_read(mess, "s", &state) < 0) {
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, MODULE_NAME, "ActiveState", err.name);
    } else  {
        for (int i=0; i<sizeof(active_state_str); ++i) {
            if (strncmp(state, active_state_str[i], strlen(state)+1) == 0) {
                r = i;
                break;
            }
        }
    }

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

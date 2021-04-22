/**
 * Module for interfacing with the OreSat GPS daemon over D-Bus.
 *
 * @file        gps.c
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "logging.h"
#include "utility.h"
#include "gps.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <systemd/sd-bus.h>

#define MODULE_NAME     "GPS"
#define DESTINATION     "org.OreSat.GPS"
#define INTERFACE_NAME  "org.OreSat.GPS"
#define OBJECT_PATH     "/org/OreSat/GPS"

/** System D-Bus connection. Defined in main.c */
extern sd_bus *system_bus;

// lazy way to deal with all the D-Bus arguments
#define DBUS_INFO system_bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

int
gps_state_vector(state_vector_t *st) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    uint32_t time_coarse, time_fine;
    int r = 0;

    if (st == NULL)
        return -EINVAL;

    if ((r = sd_bus_get_property(DBUS_INFO, "StateVector", &err, &mess, "(iiiiiiuu)")) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, MODULE_NAME, "StateVector", err.name);
    else if ((r = sd_bus_message_read(mess, "(iiiiiiuu)",
                    &st->position.x, &st->position.y, &st->position.z,
                    &st->velocity.x, &st->velocity.y, &st->velocity.z,
                    &time_coarse, &time_fine)) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, MODULE_NAME, "StateVector", err.name);

    st->timestamp.tv_sec = (time_t)time_coarse;
    st->timestamp.tv_usec = (long)time_fine;

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

uint8_t
gps_status(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    uint8_t status;

    if (sd_bus_get_property(DBUS_INFO, "Status", &err, &mess, "y") < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, MODULE_NAME, "Status", err.name);
    else if (sd_bus_message_read(mess, "y", &status) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, MODULE_NAME, "Status", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return status;
}

bool
gps_time_synchronized(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    bool sync = false;

    if (sd_bus_get_property(DBUS_INFO, "Sync", &err, &mess, "b") < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, MODULE_NAME, "Sync", err.name);
    else if (sd_bus_message_read(mess, "b", &sync) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, MODULE_NAME, "Sync", err.name);
    
    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return sync;
}

uint8_t
gps_satellite_number(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    uint8_t sats = 0;

    if (sd_bus_get_property(DBUS_INFO, "Satellites", &err, &mess, "y") < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, MODULE_NAME, "Satellites", err.name);
    else if (sd_bus_message_read(mess, "y", &sats) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, MODULE_NAME, "Satellites", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return sats;
}

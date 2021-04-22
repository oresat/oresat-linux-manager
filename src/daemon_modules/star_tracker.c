/**
 * Module for interfacing with the OreSat Star Tracker daemon over D-Bus.
 *
 * @file        star_tracker.c
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "logging.h"
#include "utility.h"
#include "star_tracker.h"
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <systemd/sd-bus.h>

#define MODULE_NAME     "Star Tracker"
#define DESTINATION     "org.OreSat.StarTracker"
#define INTERFACE_NAME  "org.OreSat.StarTracker"
#define OBJECT_PATH     "/org/OreSat/StarTracker"

/** System D-Bus connection. Defined in main.c */
extern sd_bus *system_bus;

// lazy way to deal with all the D-Bus arguments
#define DBUS_INFO system_bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

int
star_tracker_coordinates(st_coordinates_t *coor) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    double time_raw, time_fine, time_coarse;
    int r = 0;

    if (coor == NULL)
        return -EINVAL;

    if ((r = sd_bus_get_property(DBUS_INFO, "Coor", &err, &mess, "(dddd)")) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, MODULE_NAME, "Coor", err.name);
    else if ((r = sd_bus_message_read(mess, "(dddd)",
            &coor->declination,
            &coor->right_ascension,
            &coor->roll,
            &time_raw)) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, MODULE_NAME, "Coor", err.name);

    time_fine = modf(time_raw, &time_coarse);

    coor->timestamp.tv_sec = (time_t)time_coarse;
    coor->timestamp.tv_usec = (long)time_fine;

    sd_bus_error_free(&err);
    sd_bus_message_unref(mess);
    return r;
}

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

#include "log_message.h"
#include "utility.h"
#include "star_tracker.h"
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <systemd/sd-bus.h>

#define MODULE_NAME     "Star Tracker"
#define DESTINATION     "org.OreSat.StarTracker"
#define INTERFACE_NAME  "org.OreSat.StarTracker"
#define OBJECT_PATH     "/org/OreSat/StarTracker"
#define SERVICE_FILE    "oresat-star-tracker.service"

// lazy way to deal with all the D-Bus arguments
#define DBUS_INFO system_bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

/** System D-Bus connection. Defined in main.c */
extern sd_bus *system_bus;

int
star_tracker_coordinates(st_coordinates_t *coor) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r = 0;

    if (coor == NULL)
        return -EINVAL;

    if ((r = sd_bus_get_property(DBUS_INFO, "coor", &err, &mess, "(dddd)")) < 0)
        goto star_tracker_coordinates_end;

    r = sd_bus_message_read(
            mess,
            "(dddd)",
            coor->declination,
            coor->right_ascension,
            coor->roll,
            coor->timestamp);
    if (r != 0)
        return r;

star_tracker_coordinates_end:

    sd_bus_error_free(&err);
    sd_bus_message_unref(mess);
    return r;
}

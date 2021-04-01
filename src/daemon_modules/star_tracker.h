/**
 * Module for interfacing with the OreSat Star Tracker daemon over D-Bus.
 *
 * @file        star_tracker.h
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef STAR_TRACKER_MODULE_H
#define STAR_TRACKER_MODULE_H

#include "olm_app.h"

typedef struct {
    double declination;
    double right_ascension;
    double roll;
    double timestamp; // TODO fix type
} st_coordinates_t;

int star_tracker_app(olm_app_t *app);
int star_tracker_coordinates(st_coordinates_t *coor);

#endif /* STAR_TRACKER_MODULE_H */

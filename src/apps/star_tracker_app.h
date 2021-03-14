/**
 * OreSat Star Tracker daemon app.
 *
 * @file        star_tracker_app.h
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef STAR_TRACKER_APP_H
#define STAR_TRACKER_APP_H

#include "olm_app.h"

typedef struct {
    double declination;
    double right_ascension;
    double roll;
    double timestamp; // TODO fix type
} st_coordinates_t;

olm_app_t* star_tracker_app_create(void);
int star_tracker_coordinates(st_coordinates_t *coor);

#endif /* STAR_TRACKER_APP_H */

/**
 * Module for interfacing with the OreSat Star Tracker daemon over D-Bus.
 *
 * @file        star_tracker.h
 * @ingroup     daemons
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef STAR_TRACKER_MODULE_H
#define STAR_TRACKER_MODULE_H

#include <stdint.h>
#include <sys/time.h>

#define STAR_TRACKER_SERVICE_FILE "oresat-star-trackerd.service"

typedef struct {
    double declination;
    double right_ascension;
    double roll;
    struct timeval timestamp;
} st_coordinates_t;

/**
 * @breif gets the current orientation cordinates.
 *
 * @param coor The cordinates stuct to fill out.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int star_tracker_coordinates(st_coordinates_t *coor);

/**
 * @brief Gets the curret state.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int32_t star_tracker_state(void);

/**
 * @breif Tells the star tracker to change states.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int star_tracker_change_state(int32_t new_state);

/**
 * @breif Tells star tracker to capture an image.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int star_tracker_capture(void);

/**
 * @breif Gets path to last capture image.
 *
 * @param out The filepath to image. String musta
 * be freed with free() when no longer needed.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int star_tracker_get_capture(char **out);

/**
 * @breif Gets path to last solve image.
 *
 * @param out The filepath to image. String musta
 * be freed with free() when no longer needed.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int star_tracker_get_solve(char **out);

#endif /* STAR_TRACKER_MODULE_H */

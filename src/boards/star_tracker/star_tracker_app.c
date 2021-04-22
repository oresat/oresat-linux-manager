/**
 * OreSat Star Tracker app.
 *
 * @file        star_tracker_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "CANopen.h"
#include "ecss_time.h"
#include "olm_file_cache.h"
#include "star_tracker.h"
#include "star_tracker_app.h"
#include <stdbool.h>
#include <stdint.h>

#define TPDO_ST_COOR_TIME   2
#define TPDO_ST_COOR        3
#define TPDO_ST_GENERAL     4

void
star_tracker_app_async(void *data, olm_file_cache_t *fread_cache) {
    st_coordinates_t coor;
    time_scet_t time;

    if (!CO->TPDO[TPDO_ST_GENERAL]->valid) {
        CO_LOCK_OD();
        CO->TPDO[TPDO_ST_GENERAL]->valid = true;
        CO_UNLOCK_OD();
    }

    if (star_tracker_coordinates(&coor) >= 0) {
        time.coarse = coor.timestamp.tv_sec;
        time.fine = coor.timestamp.tv_usec;

        CO_LOCK_OD();
        CO->TPDO[TPDO_ST_COOR_TIME]->valid = true;
        CO->TPDO[TPDO_ST_COOR]->valid = true;
        OD_orienation.rightAscension = (int16_t)coor.right_ascension;
        OD_orienation.declination = (int16_t)coor.declination;
        OD_orienation.roll = (int16_t)coor.roll;
        OD_orienation.timestamp = time.raw;
        CO_UNLOCK_OD();
    }
}

void
star_tracker_app_end(void *data) {
    CO_LOCK_OD();
    CO->TPDO[TPDO_ST_GENERAL]->valid = false;
    CO->TPDO[TPDO_ST_COOR_TIME]->valid = false;
    CO->TPDO[TPDO_ST_COOR]->valid = false;
    OD_starTrackerStatus = 0xFF;
    CO_UNLOCK_OD();
}

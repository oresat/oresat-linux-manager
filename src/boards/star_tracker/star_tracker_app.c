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
#include "utility.h"
#include "olm_file_cache.h"
#include "star_tracker.h"
#include "star_tracker_app.h"
#include <time.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define TPDO_ST_COOR_TIME   2
#define TPDO_ST_COOR        3
#define TPDO_ST_GENERAL     4

static uint8_t current_state = -1;

void
star_tracker_app_async(void *data, olm_file_cache_t *fread_cache) {
    st_coordinates_t coor;
    time_scet_t scet;
    uint8_t temp;
    uint32_t temp2;
    char *path;
    time_t mytime;
    char temp_path[PATH_MAX];


    if (!CO->TPDO[TPDO_ST_GENERAL]->valid) {
        CO_LOCK_OD();
        CO->TPDO[TPDO_ST_GENERAL]->valid = true;
        CO_UNLOCK_OD();
    }

    CO_LOCK_OD();
    temp = OD_starTrackerStatus;
    CO_UNLOCK_OD();

    if (temp == 0 || temp == 1)
        star_tracker_change_state((int32_t)temp);

    temp2 = star_tracker_state();
    current_state = (uint8_t)temp2;

    if (current_state == 1 || current_state == 0) {
        CO->TPDO[TPDO_ST_COOR_TIME]->valid = true;
        CO->TPDO[TPDO_ST_COOR]->valid = true;
    }

    if (current_state == 1  && star_tracker_coordinates(&coor) >= 0) {
        scet.coarse = coor.timestamp.tv_sec;
        scet.fine = coor.timestamp.tv_usec;

        CO_LOCK_OD();
        OD_orienation.rightAscension = (int16_t)coor.right_ascension;
        OD_orienation.declination = (int16_t)coor.declination;
        OD_orienation.roll = (int16_t)coor.roll;
        OD_orienation.timestamp = scet.raw;
        CO_UNLOCK_OD();
    }

    if (OD_capture) {
        star_tracker_capture();
        if (star_tracker_get_capture(&path) >= 0) {
            mytime = time(NULL);
            sprintf(temp_path, "star-tracker_capture_%ld", mytime);

            copyfile(path, temp_path);
            free(path);

            if (olm_file_cache_add(fread_cache, temp_path) < 0)
                log_printf(LOG_ERR, "failed to add %s to fread cache", temp_path);
        }
        OD_capture = false;
    }

    if (OD_getLastSolveImage) {
        if (star_tracker_get_solve(&path) >= 0) {
            mytime = time(NULL);
            sprintf(temp_path, "star-tracker_solve_%ld", mytime);

            copyfile(path, temp_path);
            free(path);

            if (olm_file_cache_add(fread_cache, temp_path) < 0)
                log_printf(LOG_ERR, "failed to add %s to fread cache", temp_path);
        }
        OD_getLastSolveImage = false;
    }
}

void
star_tracker_app_end(void *data) {
    CO_LOCK_OD();
    CO->TPDO[TPDO_ST_GENERAL]->valid = false;
    CO->TPDO[TPDO_ST_COOR_TIME]->valid = false;
    CO->TPDO[TPDO_ST_COOR]->valid = false;
    current_state = 0xFF;
    CO_UNLOCK_OD();
}

CO_SDO_abortCode_t
star_tracker_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    uint8_t temp;

    if (ODF_arg->subIndex == OD_3100_3_updater_listUpdates) { // state, uint8_t, readwrite
        if (ODF_arg->reading) {
            CO_setUint8(ODF_arg->data, current_state);
        } else {
            temp = CO_getUint8(ODF_arg->data);
            if (temp != 0 || temp != 1)
                return CO_SDO_AB_GENERAL;
        }
    }

    return ret;
}

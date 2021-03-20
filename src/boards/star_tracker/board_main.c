/**
 *: Board main for the OreSat Star Tracker board.
 *
 * @file        board_main.c
 * @ingroup     star_tracker
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "CANopen.h"
#include "olm_app.h"
#include "linux_updater_app.h"
#include "star_tracker_app.h"
#include "board_main.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// apps index in list
#define LINUX_UPDATER_APP   0 // linux_updater_app is always 0
#define STAR_TRACKER_APP    LINUX_UPDATER_APP+1
#define TOTAL_APPS          STAR_TRACKER_APP+1

olm_app_t apps[TOTAL_APPS] = {OLM_APP_INITIALIZER};

olm_app_t *
board_init(void) {
    linux_updater_app(&apps[LINUX_UPDATER_APP]);
    star_tracker_app(&apps[STAR_TRACKER_APP]);
    return apps;
}

void
board_loop(void) {
    st_coordinates_t coor;

    if (apps[STAR_TRACKER_APP].unit_active_state == unit_active) {
        printf("coor\n");
        if (star_tracker_app_coordinates(&coor) >= 0) {
            CO_LOCK_OD();
            OD_orienation.rightAscension = coor.right_ascension;
            OD_orienation.declination = coor.declination;
            OD_orienation.roll = coor.roll;
            // TODO time stamp
            CO_UNLOCK_OD();
        }
    }
    usleep(1000000);
}

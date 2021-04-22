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
#include "updaterd.h"
#include "star_tracker_app.h"
#include "updater_app.h"
#include "olm_app.h"
#include "board_main.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static olm_app_t updater_app = {
    .name = "Updater",
    .unit_name = UPDATER_SERVICE_FILE,
    .fwrite_keyword = "update",
    .fwrite_cb = updaterd_add_update_archive,
    .async_cb = updater_async,
    .daemon_end_cb = updater_end,
    .data = NULL,
};

static olm_app_t star_tracker_app = {
    .name = "Star Tracker",
    .unit_name = STAR_TRACKER_SERVICE_FILE,
    .fwrite_keyword = NULL,
    .fwrite_cb = NULL,
    .async_cb = star_tracker_app_async,
    .daemon_end_cb = star_tracker_app_end,
    .data = NULL,
};

static olm_app_t *apps[] = {
    &updater_app, // updater app is always index 0
    &star_tracker_app,
    NULL, // always end with null
};

// global shared with main.c
olm_app_t **APPS = apps;

void
board_init(void) {
    CO_OD_configure(CO->SDO[0], OD_3100_updater, updater_ODF, NULL, 0, 0U);
    CO_OD_configure(CO->SDO[0], OD_6003_changeState, star_tracker_ODF, NULL, 0, 0U);
}

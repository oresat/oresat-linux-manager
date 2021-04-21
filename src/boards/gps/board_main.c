/**
 * Board main for the OreSat GPS board.
 *
 * @file        board_main.c
 * @ingroup     gps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "CANopen.h"
#include "updaterd.h"
#include "updater_app.h"
#include "olm_app.h"
#include "gps.h"
#include "gps_app.h"
#include "board_main.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
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

static olm_app_t gps_app = {
    .name = "GPS",
    .unit_name = GPS_SERVICE_FILE,
    .fwrite_keyword = NULL,
    .fwrite_cb = NULL,
    .async_cb = gps_app_async,
    .daemon_end_cb = gps_app_end,
    .data = NULL,
};


static olm_app_t *apps[] = {
    &updater_app, // updater app is always index 0
    &gps_app,
    NULL, // always end with null
};

// global shared with main.c
olm_app_t **APPS = apps;

void
board_init(void) {
    CO_OD_configure(CO->SDO[0], OD_3100_updater, updater_ODF, NULL, 0, 0U);
}

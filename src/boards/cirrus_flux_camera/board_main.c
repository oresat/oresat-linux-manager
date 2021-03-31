/**
 * Board main for the OreSat CFC board.
 *
 * @file        board_main.c
 * @ingroup     cfc
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "globals.h"
#include "CANopen.h"
#include "olm_app.h"
#include "updater_app.h"
#include "updater_odf.h"
#include "board_main.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

// apps index in list
#define UPDATER_APP         0 // linux_updater_app is always 0
#define TOTAL_APPS          UPDATER_APP+1

olm_app_t apps[TOTAL_APPS] = {OLM_APP_DEFAULT};

int
board_init(olm_board_t *board) {

    if (board == NULL)
        return -EINVAL;

    // fill out info for all apps
    updater_app(&apps[UPDATER_APP]);

    board->apps_len = TOTAL_APPS;
    board->apps = apps;

    // ODFs
    CO_OD_configure(CO->SDO[0], OD_3100_updater, updater_ODF, NULL, 0, 0U);

    return 1;
}

void
board_loop(void) {
    updater_async(fwrite_cache);
    usleep(100000);
}

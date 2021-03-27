/**
 * Board main for the OreSat Live board.
 *
 * @file        board_main.c
 * @ingroup     oresat_live
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "CANopen.h"
#include "olm_app.h"
#include "dxwifi_app.h"
#include "updater_app.h"
#include "board_main.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

// apps index in list
#define UPDATER_APP         0 // linux_updater_app is always 0
#define DXWIFI_APP          UPDATER_APP+1
#define TOTAL_APPS          DXWIFI_APP+1

olm_app_t apps[TOTAL_APPS] = {OLM_APP_INITIALIZER};

olm_app_t *
board_init(void) {
    updater_app(&apps[UPDATER_APP]);
    dxwifi_app(&apps[DXWIFI_APP]);
    return apps;
}

void
board_loop(void) {
    usleep(100000);
}

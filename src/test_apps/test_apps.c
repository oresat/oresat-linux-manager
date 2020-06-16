/**
 * Apps for testing/debugging.
 *
 * @file        test_apps.c
 * @ingroup     test_apps
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "system_apps.h"
#include "app_OD_helpers.h"
#include "daemon_controller.h"
#include "file_transfer.h"
#include "OD_app.h"


int
setup_test_apps(void) {
    setup_OD_app();


    return 1;
}

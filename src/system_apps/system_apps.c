/**
 * App for the Linux updater dameon.
 *
 * @file        system_apps.c
 * @ingroup     system_apps
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "apps.h"
#include "linux_updater_app.h"
#include "power_management_app.h"


int
setup_system_apps(void) {
#ifdef DEBUG
    OD_app_setup();
#endif

    power_management_app_setup();
    linux_updater_app_setup();

    return 1;
}

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
#include "logind_app.h"
#include "systemd_app.h"


int
system_apps_setup(void) {

    systemd_app_setup();
    logind_app_setup();
    linux_updater_app_setup();

    return 1;
}

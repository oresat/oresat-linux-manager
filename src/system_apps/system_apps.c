/**
 * App for the Linux updater dameon.
 *
 * @file        system_apps.c
 * @ingroup     system_apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#include "apps.h"
#include "linux_updater_app.h"


int
system_apps_setup(void) {

    linux_updater_app_setup();

    return 1;
}

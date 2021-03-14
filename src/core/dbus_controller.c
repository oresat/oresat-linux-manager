/**
 * The dbus controller for all apps.
 *
 * @file        dbus_controller.c
 * @ingroup     dbus_controller
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#include "log_message.h"
#include "olm_app.h"
#include "dbus_controller.h"
#include <errno.h>
#include <sys/syslog.h>
#include <systemd/sd-bus.h>


/** GLOBAL to hold all the app dbus info */
dbus_data_t      APP_DBUS;


int
dbus_controller_init(void) {
    int r;

    // open bus
    if((r = sd_bus_open_system(&APP_DBUS.bus)) < 0)
        log_message(LOG_CRIT, "Open system bus for apps failed\n");

    return r;
}


int
dbus_controller_loop(void) {
    int r;
    APP_DBUS.loop_running = true;

    while(APP_DBUS.loop_running) {
        // Process requests
        if((r = sd_bus_process(APP_DBUS.bus, NULL)) < 0)
            log_message(LOG_ERR, "Process bus failed for apps\n");
        else if (r > 0) // processed a request, try to process another one right-away
            continue;

        // Wait for the next request to process
        if(sd_bus_wait(APP_DBUS.bus, UINT64_MAX) < 0)
            log_message(LOG_ERR, "Bus wait failed for apps\n");
    }

    APP_DBUS.loop_running = false;
    return 0;
}


int
dbus_controller_end(void) {
    APP_DBUS.loop_running = false;

    // close bus
    if(APP_DBUS.bus == NULL) {
        sd_bus_unref(APP_DBUS.bus);
        APP_DBUS.bus = NULL;
    }

    return 0;
}

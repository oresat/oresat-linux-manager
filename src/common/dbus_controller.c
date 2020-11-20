/**
 * The dbus controller for all apps.
 *
 * @file        dbus_controller.c
 * @ingroup     dbus_controller
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "log_message.h"
#include <sys/syslog.h>
#include <systemd/sd-bus.h>
#include <stdbool.h>
#include "dbus_controller.h"
#include "apps.h"


/** GLOBAL to hold all the app dbus info */
dbus_data_t      APP_DBUS;


int
dbus_controller_init() {
    int r;

    // open bus
    if((r = sd_bus_open_system(&APP_DBUS.bus)) < 0)
        log_message(LOG_CRIT, "Open system bus for apps failed\n");

    return r;
}


int
dbus_controller_setup_apps() {
    int r = 0;

    r += system_apps_setup();
    r += board_apps_setup();

    log_message(LOG_DEBUG, "%d apps added");

    return r;
}



int
dbus_controller_loop() {
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
dbus_controller_end() {
    APP_DBUS.loop_running = false;

    // close bus
    if(APP_DBUS.bus == NULL) {
        sd_bus_unref(APP_DBUS.bus);
        APP_DBUS.bus = NULL;
    }

    return 0;
}

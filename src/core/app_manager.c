/**
 * The OLM app manager.
 *
 * @file        app_manager.c
 * @ingroup     app_manager
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#include "log_message.h"
#include "olm_app.h"
#include "app_manager.h"
#include <errno.h>
#include <sys/syslog.h>
#include <systemd/sd-bus.h>

/** For @ref sd_bus_wait to return after x microseconds. */
#define TIMEOUT_US 1000000

/** GLOBAL to hold all the app dbus info */
dbus_data_t      APP_DBUS;


int
app_manager_init(void) {
    int r;

    log_message(LOG_DEBUG, "openning dbus connection");

    // open bus
    if((r = sd_bus_open_system(&APP_DBUS.bus)) < 0)
        log_message(LOG_CRIT, "open system bus for apps failed");

    return r;
}


int
app_manager_dbus_loop(void) {
    APP_DBUS.loop_running = true;
    int r;

    while(APP_DBUS.loop_running) {
        // Process requests
        if((r = sd_bus_process(APP_DBUS.bus, NULL)) < 0)
            log_message(LOG_ERR, "process bus failed for apps");
        else if (r > 0) // processed a request, try to process another one right-away
            continue;

        // Wait for the next request to process
        if(sd_bus_wait(APP_DBUS.bus, TIMEOUT_US) < 0)
            log_message(LOG_ERR, "bus wait failed");
    }

    APP_DBUS.loop_running = false;
    return 0;
}


int
app_manager_end(void) {
    APP_DBUS.loop_running = false;

    log_message(LOG_DEBUG, "closed dbus connection");

    // close bus
    if(APP_DBUS.bus == NULL) {
        sd_bus_unref(APP_DBUS.bus);
        APP_DBUS.bus = NULL;
    }

    return 0;
}

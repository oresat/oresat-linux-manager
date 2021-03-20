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
#define TIMEOUT_US 10000

extern volatile sig_atomic_t CO_endProgram; // defined in main.c

/** GLOBAL to hold all the app dbus info */
dbus_data_t      APP_DBUS;

void
app_manager_dbus_run(void) {
    int r;

    if ((r = sd_bus_open_system(&APP_DBUS.bus)) < 0) {
        log_message(LOG_CRIT, "open system bus for apps failed");
        return;
    }

    log_message(LOG_CRIT, "bus client %d", sd_bus_is_bus_client(APP_DBUS.bus));

    while (CO_endProgram == 0) {
        if ((r = sd_bus_process(APP_DBUS.bus, NULL)) < 0) {
            log_message(LOG_CRIT, "sd_bus_process failed");
            break;
        } else if (r > 0) {
            continue; // processed a request, try to process another one right-away
        }

        // Wait for the next request to process
        if (sd_bus_wait(APP_DBUS.bus, TIMEOUT_US) < 0)
            log_message(LOG_ERR, "bus wait failed");
    }

    sd_bus_unref(APP_DBUS.bus);
    APP_DBUS.bus = NULL;
}

#include "log_message.h"
#include "app_dbus_controller.h"


/* Gobal for all apps to use.
 * Outside of app_dbus_controller.c it should be treated as readonly.
 */
app_dbus_data_t APPS_DBUS;


int
apps_dbus_start() {
    int r;

    r = sd_bus_open_system(&APPS_DBUS.bus);

    if(r < 0)
        log_message(LOG_CRIT, "Open system bus for apps failed\n");

    return r;
}


int
apps_dbus_main() {
    int r;
    APPS_DBUS.loop_running = true;

    while(APPS_DBUS.loop_running) {
        // Process requests
        r = sd_bus_process(APPS_DBUS.bus, NULL);
        if(r < 0)
            log_message(LOG_ERR, "Process bus failed for apps\n");
        else if (r > 0) // processed a request, try to process another one right-away
            continue;

        // Wait for the next request to process
        if(sd_bus_wait(APPS_DBUS.bus, UINT64_MAX) < 0)
            log_message(LOG_ERR, "Bus wait failed for apps\n");
    }

    APPS_DBUS.loop_running = false;
    return 1;
}


int
apps_dbus_end() {
    APPS_DBUS.loop_running = false;

    if(APPS_DBUS.bus == NULL) {
        sd_bus_unref(APPS_DBUS.bus);
        APPS_DBUS.bus = NULL;
    }

    return 1;
}



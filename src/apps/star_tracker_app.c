/**
 * OreSat Star Tracker daemon app.
 *
 * @file        star_tracker_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "log_message.h"
#include "olm_app.h"
#include "utility.h"
#include "dbus_controller.h"
#include "star_tracker_app.h"
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <systemd/sd-bus.h>

/** App's name */
#define APP_NAME        "Star Tracker"
/** D-Bus destination for app's dameon */
#define DESTINATION     "org.OreSat.StarTracker"
/** D-Bus interface for app's dameon */
#define INTERFACE_NAME  "org.OreSat.StarTracker"
/** D-Bus object for app's dameon */
#define OBJECT_PATH     "/org/OreSat/StarTracker"
/** The systemd service name for the app's daemon */
#define SERVICE_FILE    "oresat-star-tracker.service"

/**
 * Gobal for all apps to use to get access to the OLM's
 * D-Bus connections. Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;

// lazy way to deal with all the D-Bus arguments
#define DBUS_INFO APP_DBUS.bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

olm_app_t*
star_tracker_app_create(void) {
    olm_app_t *app;
   
    OLM_APP_MALLOC_AND_NULL(app);
    if (app == NULL) {
        log_message(LOG_ERR, "olm_app_malloc() failed");
        return app;
    }

    MALLOC_STRNCPY_OR_GOTO(app->name, APP_NAME, star_tracker_app_error)
    MALLOC_STRNCPY_OR_GOTO(app->service_file, SERVICE_FILE, star_tracker_app_error)

    return app;

star_tracker_app_error:

    OLM_APP_FREE(app);
    return NULL;
}

int
star_tracker_coordinates(st_coordinates_t *coor) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r = 0;

    if (coor == NULL)
        return -EINVAL;

    if ((r = sd_bus_get_property(DBUS_INFO, "coor", &err, &mess, "(dddd)")) < 0)
        goto star_tracker_coordinates_end;

    r = sd_bus_message_read(
            mess,
            "(dddd)",
            coor->declination,
            coor->right_ascension,
            coor->roll,
            coor->timestamp);
    if (r != 0)
        return r;

star_tracker_coordinates_end:

    sd_bus_error_free(&err);
    sd_bus_message_unref(mess);
    return r;
}
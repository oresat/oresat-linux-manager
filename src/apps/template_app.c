/**
 * Template app.
 *
 * @file        template_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "log_message.h"
#include "olm_app.h"
#include "utility.h"
#include "app_manager.h"
#include "template_app.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <systemd/sd-bus.h>

/** App's name */
#define APP_NAME            "Template"
/** D-Bus destionation for OreSat Linux Updater dameon */
#define DESTINATION          "org.oresat.template"
/** D-Bus interface name for OreSat Linux Updater dameon */
#define INTERFACE_NAME      DESTINATION
/** D-Bus object path for OreSat Linux Updater dameon */
#define OBJECT_PATH         "/org/oresat/template"
/** The systemd service name for the app's daemon */
#define SERVICE_FILE        "oresat-linux-templated.service"
/** The app's unique keyword for receiving files written over can */
#define FWRITE_KEYWORD      "template"

/**
 * Gobal for all apps to use to get access to the OLM's
 * D-Bus connections. Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;

// lazy way to deal with all the D-Bus arguments
#define DBUS_INFO APP_DBUS.bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

olm_app_t*
template_app_create(void) {
    olm_app_t *app;
    
    OLM_APP_MALLOC_AND_NULL(app);
    if (app == NULL) {
        log_message(LOG_ERR, "olm_app_malloc() failed");
        return app;
    }

    MALLOC_STRNCPY_OR_GOTO(app->name, APP_NAME, template_app_error)
    MALLOC_STRNCPY_OR_GOTO(app->service_file, SERVICE_FILE, template_app_error)
    MALLOC_STRNCPY_OR_GOTO(app->fwrite_keyword, FWRITE_KEYWORD, template_app_error)
    app->fwrite_cb = template_app_fwrite_file;

    return app;

template_app_error:

    OLM_APP_FREE(app);
    return NULL;
}

int
template_app_fwrite_file(const char *file) {

    // call dbus method to alert/send/copy file to daemon.

    return 0;
}


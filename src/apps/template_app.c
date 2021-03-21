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

#include "globals.h"
#include "log_message.h"
#include "olm_app.h"
#include "utility.h"
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

// lazy way to deal with all the D-Bus arguments
#define DBUS_INFO system_bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

int
template_app(olm_app_t *app) {
    MALLOC_STRNCPY_OR_GOTO(app->name, APP_NAME, template_app_error);
    MALLOC_STRNCPY_OR_GOTO(app->service_file, SERVICE_FILE, template_app_error);
    MALLOC_STRNCPY_OR_GOTO(app->fwrite_keyword, FWRITE_KEYWORD, template_app_error);
    app->fwrite_cb = template_app_fwrite_file;

    return 1;

template_app_error:

    OLM_APP_FREE(app);
    return -1;
}

int
template_app_fwrite_file(const char *file) {

    // call dbus method to alert/send/copy file to daemon.

    return 0;
}


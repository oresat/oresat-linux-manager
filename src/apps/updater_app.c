/**
 * OreSat Linux Updater daemon app.
 *
 * @file        updater_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "globals.h"
#include "log_message.h"
#include "utility.h"
#include "olm_file_cache.h"
#include "olm_app.h"
#include "updater_app.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <systemd/sd-bus.h>

/** App's name */
#define APP_NAME            "Updater"
/** D-Bus destionation for OreSat Linux Updater dameon */
#define DESTINATION         "org.oresat.updater"
/** D-Bus interface name for OreSat Linux Updater dameon */
#define INTERFACE_NAME      DESTINATION
/** D-Bus object path for OreSat Linux Updater dameon */
#define OBJECT_PATH         "/org/oresat/updater"
/** The systemd service name for the app's daemon */
#define SERVICE_FILE        "oresat-linux-updaterd.service"
/** The app's unique keyword for receiving files written over can */
#define FWRITE_KEYWORD      "update"

// lazy way to deal with all the D-Bus arguments
#define DBUS_INFO system_bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

int
updater_app(olm_app_t *app) {
    int r = 0;

    MALLOC_STRNCPY_OR_GOTO(app->name, APP_NAME, updater_app_error)
    MALLOC_STRNCPY_OR_GOTO(app->service_file, SERVICE_FILE, updater_app_error)
    MALLOC_STRNCPY_OR_GOTO(app->fwrite_keyword, FWRITE_KEYWORD, updater_app_error)
    app->fwrite_cb = updater_app_add_update_archive;

    return r;

updater_app_error:

    OLM_APP_FREE(app);
    return -1;
}

int
updater_app_add_update_archive(const char *file) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    bool value = false;
    int r = 0;

    if (file == NULL)
        return -EINVAL;

    if ((r = sd_bus_call_method(DBUS_INFO, "AddUpdateFile", &err, &mess, "s", file)) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "AddUpdateFile", err.name);
    else if ((r = sd_bus_message_read(mess, "b", &value)) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, APP_NAME, "AddUpdateFile", err.name);

    if (r == 0 && value == true)
        r = 1;

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updater_app_update(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r = 0;

    if ((r = sd_bus_call_method(DBUS_INFO, "Update", &err, &mess, NULL)) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, APP_NAME, "Update", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updater_app_make_status_archive(void) { 
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r = 0;

    if ((r = sd_bus_call_method(DBUS_INFO, "MakeStatusArchive", &err, &mess, NULL)) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "MakeStatusArchive", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updater_app_status(uint8_t *state) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r = 0;

    if ((r = sd_bus_get_property(DBUS_INFO, "StatusValue", &err, &mess, "y")) < 0)
        LOG_DBUS_GET_PROPERTY_ERROR(LOG_ERR, APP_NAME, "StatusValue", err.name);
    else if ((r = sd_bus_message_read(mess, "y", state)) < 0)
        LOG_DBUS_PROPERTY_READ_ERROR(LOG_ERR, APP_NAME, "StatusValue", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updater_app_updates_available(uint32_t *count) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r = 0;

    if ((r = sd_bus_get_property(DBUS_INFO, "AvailableUpdateArchives", &err, &mess, "u")) < 0)
        LOG_DBUS_GET_PROPERTY_ERROR(LOG_ERR, APP_NAME, "AvailableUpdateArchives", err.name);
    else if ((r = sd_bus_message_read(mess, "u", count)) < 0)
        LOG_DBUS_PROPERTY_READ_ERROR(LOG_ERR, APP_NAME, "AvailableUpdateArchives", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updater_app_list_updates(char **out) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    char *temp = NULL, *update_list = NULL;
    int r = 0;

    if ((r = sd_bus_get_property(DBUS_INFO, "ListUpdates",  &err, &mess, "s")) < 0) {
        LOG_DBUS_GET_PROPERTY_ERROR(LOG_ERR, APP_NAME, "ListUpdates", err.name);
    } else if ((r = sd_bus_message_read(mess, "s", &temp)) < 0) {
        LOG_DBUS_PROPERTY_READ_ERROR(LOG_ERR, APP_NAME, "ListUpdates", err.name);
    } else {
        if ((update_list = malloc(strlen(temp))) == NULL)
            return -ENOMEM;
        strncpy(update_list, temp, strlen(temp));
        *out = update_list;
    }

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

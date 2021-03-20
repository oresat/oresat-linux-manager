/**
 * OreSat Linux Updater daemon app.
 *
 * @file        linux_updater_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "log_message.h"
#include "utility.h"
#include "olm_app.h"
#include "app_manager.h"
#include "linux_updater_app.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <systemd/sd-bus.h>

/** App's name */
#define APP_NAME            "Linux Updater"
/** D-Bus destionation for OreSat Linux Updater dameon */
#define DESTINATION          "org.oresat.updater"
/** D-Bus interface name for OreSat Linux Updater dameon */
#define INTERFACE_NAME      DESTINATION
/** D-Bus object path for OreSat Linux Updater dameon */
#define OBJECT_PATH         "/org/oresat/updater"
/** The systemd service name for the app's daemon */
#define SERVICE_FILE        "oresat-linux-updaterd.service"
/** The app's unique keyword for receiving files written over can */
#define FWRITE_KEYWORD      "update"

/**
 * Gobal for all apps to use to get access to the OLM's
 * D-Bus connections. Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;

// lazy way to deal with all the D-Bus arguments
#define DBUS_INFO APP_DBUS.bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

int
linux_updater_app(olm_app_t *app) {
    MALLOC_STRNCPY_OR_GOTO(app->name, APP_NAME, linux_updater_app_error)
    MALLOC_STRNCPY_OR_GOTO(app->service_file, SERVICE_FILE, linux_updater_app_error)
    MALLOC_STRNCPY_OR_GOTO(app->fwrite_keyword, FWRITE_KEYWORD, linux_updater_app_error)
    // app->fwrite_cb = linux_updater_app_fwrite_file; TODO

    /* TODO requires file transfer
    if ((r = sd_bus_match_signal(DBUS_INFO, "AptList", status_cb, NULL)) < 0)
        LOG_DBUS_SIGNAL_MATCH_ERROR(LOG_CRIT, APP_NAME, "Status")
    */

    return 1;

linux_updater_app_error:

    OLM_APP_FREE(app);
    return -1;
}

/*
static int
apt_list_file_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    char *file;
    linux_updater_app_t *data = (linux_updater_app_t *)userdata;

    if (data == NULL) {
        LOG_DBUS_SIGNAL_USERDATA_ERROR(LOG_ERR, APP_NAME, "CurrentUpdateFile"); 
        return 0;
    }
    
    if (sd_bus_message_read(m, "s", &file) == 0)
        data->new_file_cb(file);
    else
        LOG_DBUS_SIGNAL_READ_ERROR(LOG_ERR, APP_NAME, "CurrentUpdateFile");

    return 0;
}
*/

uint32_t
linux_updater_updates_available(void) {
    return 0; // TODO
}

int
linux_updater_app_add_update_file(const char *file) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    bool value = false;

    if (file == NULL)
        return value;

    if (sd_bus_call_method(DBUS_INFO, "AddUpdateFile", &err, &mess, "s", file) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "AddUpdateFile", err.name);
    else if (sd_bus_message_read(mess, "b", &value) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, APP_NAME, "AddUpdateFile", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return value;
}

bool
linux_updater_start_update(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    bool value = false;

    if (sd_bus_call_method(DBUS_INFO, "StartUpdate", &err, &mess, NULL) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, APP_NAME, "StartUpdate", err.name);
    else if (sd_bus_message_read(mess, "b", &value) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "StartUpdate", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return value;
}

bool
linux_updater_stop_update(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    bool value = false;

    if (sd_bus_call_method(DBUS_INFO, "StopUpdate", &err, &mess, NULL) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "StopUpdate", err.name);
    else if (sd_bus_message_read(mess, "b", &value) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, APP_NAME, "StopUpdate", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return value;
}

bool
linux_updater_reset(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    bool value = false;

    if (sd_bus_call_method(DBUS_INFO, "Reset", &err, &mess, NULL) < 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "Reset", err.name);
    else if (sd_bus_message_read(mess, "b", &value) < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, APP_NAME, "Reset", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return value;
}

bool
get_apt_list_output(void) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    bool value = false;

    if (sd_bus_call_method(DBUS_INFO, "GetAptListOutput", &err, &mess, NULL) == 0)
        LOG_DBUS_CALL_METHOD_ERROR(LOG_ERR, APP_NAME, "GetAptListOutput", err.name);
    else if (sd_bus_message_read(mess, "b", &value))
        LOG_DBUS_METHOD_READ_ERROR(LOG_ERR, APP_NAME, "GetAptListOutput", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return value;
}

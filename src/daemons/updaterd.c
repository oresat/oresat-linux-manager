/**
 * Module for interfacing with the OreSat Linux Updater daemon over D-Bus.
 *
 * @file        updater.c
 * @ingroup     daemons
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "logging.h"
#include "utility.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <systemd/sd-bus.h>

#define MODULE_NAME    "Updater"
#define DESTINATION    "org.OreSat.Updater"
#define INTERFACE_NAME DESTINATION
#define OBJECT_PATH    "/org/OreSat/Updater"

/** System D-Bus connection. Defined in main.c */
extern sd_bus *system_bus;

// lazy way to deal with all the D-Bus arguments
#define DBUS_INFO system_bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME

int
updaterd_add_update_archive(const char *file) {
    sd_bus_error    err  = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int             r, value = 0;

    if (file == NULL)
        return -EINVAL;

    r = sd_bus_call_method(DBUS_INFO, "AddUpdateArchive", &err, &mess, "s",
                           file);
    if (r < 0) {
        LOG_DBUS_CALL_METHOD_ERROR(LOG_DEBUG, MODULE_NAME, "AddUpdateArchive",
                                   err.name);
        goto update_archive_end;
    }

    r = sd_bus_message_read(mess, "b", &value);
    if (r < 0) {
        LOG_DBUS_METHOD_READ_ERROR(LOG_DEBUG, MODULE_NAME, "AddUpdateArchive",
                                   err.name);
        goto update_archive_end;
    }

    r = value;

update_archive_end:
    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updaterd_update(void) {
    sd_bus_error    err  = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int             r;

    r = sd_bus_call_method(DBUS_INFO, "Update", &err, &mess, NULL);
    if (r < 0)
        LOG_DBUS_METHOD_READ_ERROR(LOG_DEBUG, MODULE_NAME, "Update", err.name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updaterd_make_status_archive(char **out) {
    sd_bus_error    err  = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    char *          temp, *filepath;
    int             r;

    r = sd_bus_call_method(DBUS_INFO, "MakeStatusArchive", &err, &mess, NULL);
    if (r < 0) {
        LOG_DBUS_CALL_METHOD_ERROR(LOG_DEBUG, MODULE_NAME, "MakeStatusArchive",
                                   err.name);
        goto make_status_archve_end;
    }

    r = sd_bus_message_read(mess, "s", &temp);
    if (r < 0) {
        LOG_DBUS_METHOD_READ_ERROR(LOG_DEBUG, MODULE_NAME, "MakeStatusArchive",
                                   err.name);
        goto make_status_archve_end;
    }

    if ((filepath = malloc(strlen(temp) + 1)) != NULL) {
        strncpy(filepath, temp, strlen(temp) + 1);
        *out = filepath;
    } else {
        r = -ENOMEM;
    }

make_status_archve_end:
    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updaterd_status(uint8_t *state) {
    sd_bus_error    err  = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int             r;

    r = sd_bus_get_property(DBUS_INFO, "StatusValue", &err, &mess, "y");
    if (r < 0) {
        LOG_DBUS_GET_PROPERTY_ERROR(LOG_DEBUG, MODULE_NAME, "StatusValue",
                                    err.name);
        goto status_end;
    }

    r = sd_bus_message_read(mess, "y", state);
    if (r < 0)
        LOG_DBUS_PROPERTY_READ_ERROR(LOG_DEBUG, MODULE_NAME, "StatusValue",
                                     err.name);

status_end:
    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updaterd_updates_available(uint32_t *count) {
    sd_bus_error    err  = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int             r;

    r = sd_bus_get_property(DBUS_INFO, "AvailableUpdateArchives", &err, &mess,
                            "u");
    if (r < 0) {
        LOG_DBUS_GET_PROPERTY_ERROR(LOG_DEBUG, MODULE_NAME,
                                    "AvailableUpdateArchives", err.name);
        goto updates_available_end;
    }

    r = sd_bus_message_read(mess, "u", count);
    if (r < 0)
        LOG_DBUS_PROPERTY_READ_ERROR(LOG_DEBUG, MODULE_NAME,
                                     "AvailableUpdateArchives", err.name);

updates_available_end:
    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

int
updaterd_list_updates(char **out) {
    sd_bus_error    err  = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    char *          temp = NULL, *update_list = NULL;
    int             r;

    r = sd_bus_get_property(DBUS_INFO, "ListUpdates", &err, &mess, "s");
    if (r < 0) {
        LOG_DBUS_GET_PROPERTY_ERROR(LOG_DEBUG, MODULE_NAME, "ListUpdates",
                                    err.name);
        goto list_updates_end;
    }

    r = sd_bus_message_read(mess, "s", &temp);
    if (r < 0) {
        LOG_DBUS_PROPERTY_READ_ERROR(LOG_DEBUG, MODULE_NAME, "ListUpdates",
                                     err.name);
        goto list_updates_end;
    }

    if (temp != NULL) {
        if ((update_list = malloc(strlen(temp) + 1)) == NULL) {
            r = -ENOMEM;
        } else {
            strncpy(update_list, temp, strlen(temp) + 1);
            *out = update_list;
        }
    }

list_updates_end:
    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}

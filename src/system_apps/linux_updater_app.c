/**
 * App for the Linux updater dameon.
 *
 * @file        linux_updater_app.c
 * @ingroup     linux_updater_app
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "app_helpers.h"
#include "linux_updater_app.h"
#include <systemd/sd-bus.h>


/** oresat board */
#define BOARD               "gps" // TODO fix cmake
/** App's name */
#define APP_NAME            "Linux Updater"
/** Dbus destionation for OreSat Linux Updater dameon */
#define DESTINATION          "org.OreSat.LinuxUpdater"
/** Dbus interface name for OreSat Linux Updater dameon */
#define INTERFACE_NAME      DESTINATION
/** Dbus object path for OreSat Linux Updater dameon */
#define OBJECT_PATH         "/org/OreSat/LinuxUpdater"
/** Max size for file name string */
#define FILE_NAME_SIZE      100
/** OD index for updater app ODF */
#define UPDATER_ODF_INDEX   0x3004


/** Hold all the app dbus info */
extern app_dbus_data_t      APPS_DBUS;
/* Holds the current state of the updater. */
static int32_t              current_state = 0;
/* The number archive files available. */
static uint32_t             updates_available = 0;
/** If an updating, this holds the name of archive file. */
static char                 current_file[FILE_NAME_SIZE] = "\0";


int
linux_updater_app_setup() {
    int r = 0;

    app_OD_configure(UPDATER_ODF_INDEX, updater_ODF, NULL, 0, 0U);
    app_register_daemon("Linux Updater", "oresat-linux-updaterd.service");
    app_add_request_recv_file(
            "Linux Updater",
            "^("BOARD"\\-update\\-\\d{4}\\-\\d{2}\\-\\d{2}\\-\\d{2}\\-\\d{2}\\.tar\\.gz)$",
            "/tmp/oresat-linux-updater/cache/",
            NULL);

    r = sd_bus_match_signal(
            APPS_DBUS.bus,
            NULL,
            INTERFACE_NAME,
            OBJECT_PATH,
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            read_status_cb,
            NULL);
    if (r < 0)
        app_log_message(APP_NAME, LOG_CRIT, "Signal match PropertiesChanged failed");

    return 1;
}


int
read_status_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    int r;

    r = sd_bus_get_property(
            APPS_DBUS.bus,
            CANDAEMON_DESTINATION,
            OBJECT_PATH,
            INTERFACE_NAME,
            "Status",
            ret_error,
            &m,
            "i");
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Getting property Status failed");
        return r;
    }

    r = sd_bus_message_read(m, "i", &current_state);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Reading property Status failed");
        return r;
    }

    r = sd_bus_get_property(
            APPS_DBUS.bus,
            DESTINATION,
            OBJECT_PATH,
            INTERFACE_NAME,
            "CurrentUpdateFile",
            ret_error,
            &m,
            "s");
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Getting property CurrentUpdateFile failed");
        return r;
    }

    r = sd_bus_message_read(m, "s", &current_file);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Reading property CurrentUpdateFile failed");
        return r;
    }

    return 0;
}


CO_SDO_abortCode_t
updater_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    bool_t temp_bool;
    int r;

    switch(ODF_arg->subIndex) {
        case 1 : // current state

            if(ODF_arg->reading == true) {
                ODF_arg->dataLength = sizeof(current_state);
                memcpy(ODF_arg->data, &current_state, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, read only

            break;

        case 2 : // updates available

            if(ODF_arg->reading == true) {
                ODF_arg->dataLength = sizeof(updates_available);
                memcpy(ODF_arg->data, &updates_available, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, read only

            break;

        case 3 : // current file

            if(ODF_arg->reading == true)  {
                ODF_arg->dataLength = strlen(current_file);
                memcpy(ODF_arg->data, current_file, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, read only

            break;

        case 4 : // TODO REMOVE

            ret = CO_SDO_AB_GENERAL;

            break;

        case 5 : // give updater new file, will not update with it yet

            if(ODF_arg->reading == true) {
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
                break;
            }

            if(!APPS_DBUS.loop_running) {
                app_log_message(APP_NAME, LOG_ERR, "DBus interface is not up");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            if(ODF_arg->dataLength > FILE_PATH_MAX_LENGTH) {
                app_log_message(APP_NAME, LOG_ERR, "New archvie file path wont fit in buffer");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            // copy file name into a temp var
            char new_archive_file_path[FILE_PATH_MAX_LENGTH] = "\0";
            memcpy(new_archive_file_path, ODF_arg->data, ODF_arg->dataLength);

            if(new_archive_file_path[0] != '/') {
                app_log_message(APP_NAME, LOG_ERR, "New archive file path not an absolute path");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            r = sd_bus_call_method(
                    APPS_DBUS.bus,
                    DESTINATION,
                    OBJECT_PATH,
                    INTERFACE_NAME,
                    "AddUpdateFile",
                    &err,
                    &mess,
                    "s",
                    new_archive_file_path);
            if (r < 0) {
                app_log_message(APP_NAME, LOG_ERR, "Method call AddUpdateFile failed");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            // Parse the response message
            r = sd_bus_message_read(mess, "b", &temp_bool);
            if (r < 0) {
                app_log_message(APP_NAME, LOG_ERR, "AddUpdateFile reply message failed to be parsed");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            break;

        case 6 : // start update


            if(ODF_arg->reading == true) {
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
                break;
            }

            if(!APPS_DBUS.loop_running) {
                app_log_message(APP_NAME, LOG_ERR, "DBus interface is not up");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            r = sd_bus_call_method(
                    APPS_DBUS.bus,
                    DESTINATION,
                    OBJECT_PATH,
                    INTERFACE_NAME,
                    "StartUpdate",
                    &err,
                    &mess,
                    NULL);
            if (r < 0) {
                app_log_message(APP_NAME, LOG_ERR, "Method call StartUpdate failed");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            r = sd_bus_message_read(mess, "b", &temp_bool);
            if (r < 0) {
                app_log_message(APP_NAME, LOG_ERR, "StartUpdate reply message failed to be parsed");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            break;

        case 7 : // emergency stop update

            if(ODF_arg->reading == true) {
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
                break;
            }

            if(!APPS_DBUS.loop_running) {
                app_log_message(APP_NAME, LOG_ERR, "DBus interface is not up");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            r = sd_bus_call_method(
                    APPS_DBUS.bus,
                    DESTINATION,
                    OBJECT_PATH,
                    INTERFACE_NAME,
                    "StopUpdate",
                    &err,
                    &mess,
                    NULL);
            if (r < 0) {
                app_log_message(APP_NAME, LOG_ERR, "Method call StopUpdate failed");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            // Parse the response message
            r = sd_bus_message_read(mess, "b", &temp_bool);
            if (r < 0) {
                app_log_message(APP_NAME, LOG_ERR, "StopUpdate reply message failed to be parsed");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            break;

        case 8 : // reset linux updater

            if(ODF_arg->reading == true)
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
            else {
                r = sd_bus_call_method(
                        APPS_DBUS.bus,
                        DESTINATION,
                        OBJECT_PATH,
                        INTERFACE_NAME,
                        "Reset",
                        &err,
                        &mess,
                        NULL);
                if (r < 0) {
                    app_log_message(APP_NAME, LOG_DEBUG, "Method call Reset failed");
                    ret = CO_SDO_AB_GENERAL;
                    break;
                }

                /* Parse the response message */
                r = sd_bus_message_read(mess, "b", &temp_bool);
                if (r < 0) {
                    app_log_message(APP_NAME, LOG_ERR, "Reset reply message failed to be parsed");
                    ret = CO_SDO_AB_GENERAL;
                    break;
                 }
            }

            break;

        case 9 : // get apt update output as a file

            if(!APPS_DBUS.loop_running) { // dbus interface is not up
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            if(ODF_arg->reading == true)
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
            else {
                r = sd_bus_call_method(
                        APPS_DBUS.bus,
                        DESTINATION,
                        OBJECT_PATH,
                        INTERFACE_NAME,
                        "GetAptListOutput",
                        &err,
                        &mess,
                        NULL);
                if (r < 0) {
                    app_log_message(APP_NAME, LOG_DEBUG, "Method call GetAptListOutput failed");
                    ret = CO_SDO_AB_GENERAL;
                    break;
                }

                // Parse the response message
                r = sd_bus_message_read(mess, "b", &temp_bool);
                if (r < 0) {
                    app_log_message(APP_NAME, LOG_ERR, "GetAptListOuput reply message failed to be parsed");
                    ret = CO_SDO_AB_GENERAL;
                    break;
                }
            }

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    ODF_arg->lastSegment = true;
    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return ret;
}


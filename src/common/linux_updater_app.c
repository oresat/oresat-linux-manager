#include "log_message.h"
#include "app_OD_helpers.h"
#include "file_transfer_ODF.h"
#include "linux_updater_app.h"
#include <systemd/sd-bus.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>


#define DESTINATION         "org.OreSat.LinuxUpdater"
#define INTERFACE_NAME      "org.OreSat.LinuxUpdater"
#define OBJECT_PATH         "/org/OreSat/LinuxUpdater"
#define UPDATER_ODF_INDEX   0x3004
#define FILE_NAME_SIZE      100
#define APP_NAME            "Updater"


// Static variables
static sd_bus               *bus;
static shared_data          sd  = {false, 0, 0, "\0", PTHREAD_MUTEX_INITIALIZER};


// ***************************************************************************
// manitory functions


int linux_updater_ODF_setup(void) {
    // add of app's ODFs to OD
    app_OD_configure(UPDATER_ODF_INDEX, updater_ODF, NULL, 0, 0U);
    return 0;
}


int linux_updater_dbus_main(void) {
    int r = 0;

    r = sd_bus_open_system(&bus);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_CRIT, "Open system bus failed");
        goto END;
    }

    r = sd_bus_match_signal(
            bus,
            NULL,
            NULL,
            OBJECT_PATH,
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            read_status_cb,
            NULL);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_CRIT, "Signal match PropertiesChanged failed");
        goto END;
    }

    pthread_mutex_lock(&sd.mutex);
    sd.dbus_running = true; // setup worked, start loop
    pthread_mutex_unlock(&sd.mutex);

    while (sd.dbus_running) {
        // Process requests
        r = sd_bus_process(bus, NULL);
        if ( r < 0)
            app_log_message(APP_NAME, LOG_ERR, "Process bus failed");
        else if (r > 0) // processed a request, try to process another one right-away
            continue;

        // TODO error count timeout with goto END

        // Wait for the next request to process
        if (sd_bus_wait(bus, UINT64_MAX) < 0)
            app_log_message(APP_NAME, LOG_ERR, "Bus wait failed");
    }

END: // setup / loop failed, clean up, set running to false for ODF callbacks
    pthread_mutex_lock(&sd.mutex);
    sd.dbus_running = false;
    pthread_mutex_unlock(&sd.mutex);
    sd_bus_unref(bus);
    return -r;
}


// ***************************************************************************
// dbus call back functions


int read_status_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    int r;

    r = sd_bus_get_property(
            bus,
            DESTINATION,
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

    r = sd_bus_message_read(m, "i", &sd.current_state);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Reading property Status failed");
        return r;
    }

    r = sd_bus_get_property(
            bus,
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

    r = sd_bus_message_read(m, "s", &sd.current_file);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Reading property CurrentUpdateFile failed");
        return r;
    }

    return 0;
}


// ***************************************************************************
// CANopen ODF(s)


CO_SDO_abortCode_t updater_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    bool_t temp_bool;
    int r;

    switch(ODF_arg->subIndex) {
        case 1 : // current state

            if(ODF_arg->reading == true) {
                ODF_arg->dataLength = sizeof(sd.current_state);
                memcpy(ODF_arg->data, &sd.current_state, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, read only

            break;

        case 2 : // updates available

            if(ODF_arg->reading == true) {
                ODF_arg->dataLength = sizeof(sd.updates_available);
                memcpy(ODF_arg->data, &sd.updates_available, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, read only

            break;

        case 3 : // current file

            if(ODF_arg->reading == true)  {
                ODF_arg->dataLength = strlen(sd.current_file);
                memcpy(ODF_arg->data, sd.current_file, ODF_arg->dataLength);
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

            if(!sd.dbus_running) {
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
                    bus,
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

            if(!sd.dbus_running) {
                app_log_message(APP_NAME, LOG_ERR, "DBus interface is not up");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            r = sd_bus_call_method(
                    bus,
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

            if(!sd.dbus_running) {
                app_log_message(APP_NAME, LOG_ERR, "DBus interface is not up");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            r = sd_bus_call_method(
                    bus,
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
                        bus,
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

            if(!sd.dbus_running) { // dbus interface is not up
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            if(ODF_arg->reading == true)
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
            else {
                r = sd_bus_call_method(
                        bus,
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


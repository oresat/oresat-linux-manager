/**
 * Daemon controller for CANdaemon.
 *
 * @file        daemon_controller.c
 * @ingroup     daemon_controller
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "log_message.h"
#include "app_OD_helpers.h"
#include "file_transfer_ODF.h"
#include "daemon_controller.h"
#include "system_apps.h"
#include "board_apps.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>


/** OD index for daemon controller ODF */
#define DAEMON_CONTROLLER_OD_INDEX 0x3001


// ***************************************************************************
// private structs


/**
 * A private stuct for holding all of an app data.
 * Filled by app_register() and used by the app_controller_ODF().
 */
typedef struct {
    /** App's name */
    char *name;
    /** Service name for daemon associate with app */
    char *service_name;
    /** Status of the daemon associate with app */
    int32_t status;
} daemon_data_t;


// ***************************************************************************
// static data


/** List of dbus apps */
static daemon_data_t        *daemon_list = NULL;

/** Number of apps in apps list */
static int                  apps_count = 0;

/**
 * Pointer to the current app in apps list.
 * Only used by app daemon controller ODF.
 */
static int                  current_app = 0;

/** Mutex for accesing data in apps list */
static pthread_mutex_t      apps_mutex = PTHREAD_MUTEX_INITIALIZER;


// ***************************************************************************
// static functions


int
start_daemon(daemon_data_t *daemon) { // TODO replace with dbus call
    char command[] = "systemctl start ";
    FILE* f;

    strncat(command, daemon->service_name, strlen(daemon->service_name));
    f = popen(command, "r");
    pclose(f);
    daemon->status = running;

    //log_message(LOG_ERR, "failed to start %s", daemon->service_name);

    return 0;
}


int
stop_daemon(daemon_data_t *daemon) { // TODO replace with dbus call
    char command[] = "systemctl stop ";
    FILE* f;

    strncat(command, daemon->service_name, strlen(daemon->service_name));
    f = popen(command, "r");
    pclose(f);
    daemon->status = stopped;

    //log_message(LOG_ERR, "failed to stop %s", daemon->service_name);

    return 0;
}


// ***************************************************************************
// non static functions


int
app_register_daemon(const char *name, const char *daemon_name) {
    int new_app;

    if(apps_count > 127)
        return -1; // exceeded maxium apps allowed

    pthread_mutex_lock(&apps_mutex);

    if(apps_count == 0) { // init apps array
        apps_count = 1;
        daemon_list = (daemon_data_t *)malloc(sizeof(daemon_data_t));
    }
    else { // add an app to apps array
        ++apps_count;
        daemon_list = (daemon_data_t *)realloc(daemon_list, sizeof(daemon_data_t) * apps_count);
    }

    new_app = apps_count - 1;

    // setup app general data
    daemon_list[new_app].name = (char *)malloc(strlen(name));
    strncpy(daemon_list[new_app].name, name, strlen(name));

    // setup app daemon data
    if(daemon_name == NULL) { // no daemon to controll
        daemon_list[new_app].service_name = NULL;
    }
    else {
        daemon_list[new_app].service_name = (char *)malloc(strlen(daemon_name));
        strncpy(daemon_list[new_app].service_name, daemon_name, strlen(daemon_name));
        daemon_list[new_app].status = 0; //TODO enum
    }

    pthread_mutex_unlock(&apps_mutex);

    return new_app;
}


CO_SDO_abortCode_t
daemon_controller_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;

    switch (ODF_arg->subIndex) {
        case 1 : // select which app, uint8, readwrite

            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(current_app);
                memcpy(ODF_arg->data, &current_app, ODF_arg->dataLength);
            }
            else {
                if(ODF_arg->dataLength != sizeof(current_app)) {
                    log_error_ODF("app_controller_ODF", ODF_arg, "data size does not match");
                    return CO_SDO_AB_GENERAL; // error with data size
                }
                memcpy(&current_app, ODF_arg->data, ODF_arg->dataLength);
            }

            break;

        case 2 : // app name, domain, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = strlen(daemon_list[current_app].name);
                memcpy(ODF_arg->data, &daemon_list[current_app].name, ODF_arg->dataLength);
            }
            else {
                return CO_SDO_AB_READONLY; // can't write parameters, readonly");
            }

            break;

        case 3 : // daemon service name, domain, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(daemon_list[current_app].service_name);
                memcpy(ODF_arg->data, &daemon_list[current_app].service_name, ODF_arg->dataLength);
            }
            else
                return CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case 4 : // daemon current state, int32, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(daemon_list[current_app].status);
                memcpy(ODF_arg->data, &daemon_list[current_app].status, ODF_arg->dataLength);
            }
            else
                return CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case 5 : // daemon change state, int32, writeonly

            if(ODF_arg->reading)
                return CO_SDO_AB_WRITEONLY; // can't read parameters, writeonly
            else {
                if(ODF_arg->dataLength != sizeof(daemon_list[current_app].status)) {
                    log_error_ODF("app_controller_ODF", ODF_arg, "data size does not match");
                    return CO_SDO_AB_GENERAL; // error with data size
                }

                int32_t temp;
                memcpy(&temp, ODF_arg->data, ODF_arg->dataLength);

                if(temp == running)
                    start_daemon(&daemon_list[current_app]);
                else if(temp == stopped)
                    stop_daemon(&daemon_list[current_app]);
                else
                    log_error_ODF("app_controller_ODF", ODF_arg, "unkown input to daemon change state");
            }

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    return ret;
}



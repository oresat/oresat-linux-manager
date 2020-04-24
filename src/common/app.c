#include "log_message.h"
#include "app_OD_helpers.h"
#include "systemd_app.h"
#include "app.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


typedef struct {
    int (*thread_main)(void); // func ptr to thread main. If NULL there is no thread.
    int status; // current state of thread.
    int exit_failures; // how many time the thread has return with failure.
} ThreadData;


typedef struct {
    char *name; // app's name
    DaemonData daemon; // app's daemon data for daemon controller to use
    ThreadData thread; // app's thread data for thread controller to use.
} App;


static pthread_mutex_t      apps_mutex;
static App                  *apps = NULL;
static int                  apps_length = 0;
static int                  current_app = 0;


int app_register(
        const char *name,
        const char *daemon_name,
        int (*thread_main)(void)) {
    int new_app;

    if(apps_length > 127)
        return -1; // exceeded maxium apps allowed

    pthread_mutex_lock(&apps_mutex);

    if(apps_length == 0) { // make apps array
        apps_length = 1;
        apps = (App *)malloc(sizeof(App));
    }
    else { // add an app to apps array
        ++apps_length;
        apps = (App *)realloc(apps, sizeof(App) * apps_length);
    }

    new_app = apps_length - 1;

    // setup app general data
    apps[new_app].name = (char *)malloc(strlen(name));
    strncpy(apps[new_app].name, name, strlen(name));

    // setup app daemon data
    if(daemon_name == NULL) { // no daemon to controll
        apps[new_app].daemon.service_name = NULL;
    }
    else {
        apps[new_app].daemon.service_name = (char *)malloc(strlen(daemon_name));
        strncpy(apps[new_app].daemon.service_name, daemon_name, strlen(daemon_name));
        apps[new_app].daemon.status = 0; //TODO enum
    }

    // setup app thread data
    if(thread_main == NULL) { // no thread needed
        apps[new_app].thread.thread_main = NULL;
    }
    else {
        apps[new_app].thread.thread_main = thread_main;
        apps[new_app].thread.status = 0; // TODO enum
        apps[new_app].thread.exit_failures = 0;
    }

    pthread_mutex_unlock(&apps_mutex);

    return new_app;
}


int thd_ctrl_change_state(ThreadData thread, int32_t state) {
    return 0;
}



CO_SDO_abortCode_t app_controller_ODF(CO_ODF_arg_t *ODF_arg) {
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
                ODF_arg->dataLength = strlen(apps[current_app].name);
                memcpy(ODF_arg->data, &apps[current_app].name, ODF_arg->dataLength);
            }
            else {
                return CO_SDO_AB_READONLY; // can't write parameters, readonly");
            }

            break;

        case 3 : // app current state, int32, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(apps[current_app].thread.status);
                memcpy(ODF_arg->data, &apps[current_app].thread.status, ODF_arg->dataLength);
            }
            else
                return CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case 4 : // app change state, int32, writeonly

            if(ODF_arg->reading)
                return CO_SDO_AB_WRITEONLY; // can't read parameters, writeonly
            else {
                if(ODF_arg->dataLength != sizeof(apps[current_app].thread.status)) {
                    log_error_ODF("app_controller_ODF", ODF_arg, "data size does not match");
                    return CO_SDO_AB_GENERAL; // error with data size
                }

                int32_t temp;
                memcpy(&temp, ODF_arg->data, ODF_arg->dataLength);
                thd_ctrl_change_state(&apps[current_app].thread, temp);
            }

            break;

        case 5 : // daemon service name, domain, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(apps[current_app].daemon.service_name);
                memcpy(ODF_arg->data, &apps[current_app].daemon.service_name, ODF_arg->dataLength);
            }
            else
                return CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case 6 : // daemon current state, int32, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(apps[current_app].daemon.status);
                memcpy(ODF_arg->data, &apps[current_app].daemon.status, ODF_arg->dataLength);
            }
            else
                return CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case 7 : // daemon change state, int32, writeonly

            if(ODF_arg->reading)
                return CO_SDO_AB_WRITEONLY; // can't read parameters, writeonly
            else {
                if(ODF_arg->dataLength != sizeof(apps[current_app].daemon.status)) {
                    log_error_ODF("app_controller_ODF", ODF_arg, "data size does not match");
                    return CO_SDO_AB_GENERAL; // error with data size
                }

                int32_t temp;
                memcpy(&temp, ODF_arg->data, ODF_arg->dataLength);

                if(temp == running)
                    start_daemon(&apps[current_app].daemon);
                else if(temp == stopped)
                    stop_daemon(&apps[current_app].daemon);
                else
                    log_error_ODF("app_controller_ODF", ODF_arg, "unkown input to daemon change state");
            }

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    return ret;
}



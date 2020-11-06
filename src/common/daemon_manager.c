/**
 * Daemon manager for CANdaemon.
 *
 * @file        daemon_manager.c
 * @ingroup     daemon_manager
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "log_message.h"
#include "OD_helpers.h"
#include "daemon_manager.h"
#include "systemd_app.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>


/** OD index for daemon list ODF */
#define DAEMON_LIST_ODF_INDEX       0x3004
/** OD index for daemon manager ODF */
#define DAEMON_MANAGER_ODF_INDEX    0x3005


/** List of data for daemons registered by apps */
static daemon_data_t *daemon_list = NULL;
/** Size of daemon list */
static uint8_t daemon_list_len = 127;
/** Number of daemon in dbus list */
static uint8_t daemon_count = 0;
/** Selected daemon index in daemon list */
static uint8_t list_index = 0;
/** Mutex for accesing data */
static pthread_mutex_t dc_mutex = PTHREAD_MUTEX_INITIALIZER;


int
daemon_manager_setup() {
    // get the size of the daemon list in object dictionary
    //app_OD_read(DAEMON_LIST_ODF_INDEX, 0, &daemon_list_len, sizeof(daemon_list_len));

    // setup daemon list ODF
    CO_OD_configure(CO->SDO[0], DAEMON_LIST_ODF_INDEX, daemon_list_ODF, NULL, 0, 0U);
    CO_OD_configure(CO->SDO[0], DAEMON_MANAGER_ODF_INDEX, daemon_manager_ODF, NULL, 0, 0U);
    return 0;
}


CO_SDO_abortCode_t
daemon_list_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    int daemon_index;

    if(ODF_arg->reading) {
        if(ODF_arg->subIndex == 0) { // sub index size, uint8. readonly
            ODF_arg->dataLength = sizeof(daemon_list_len);
            memcpy(ODF_arg->data, &daemon_list_len, ODF_arg->dataLength);
        }
        else { // daemon name in list, domain, readonly
            daemon_index = (int)ODF_arg->subIndex - 1;
            ODF_arg->dataLength = strlen(daemon_list[daemon_index].name);
            memcpy(ODF_arg->data, &daemon_list[daemon_index], ODF_arg->dataLength);
        }
    }
    else
        ret = CO_SDO_AB_READONLY; // can't write parameters, readonly");

    return ret;
}


CO_SDO_abortCode_t
daemon_manager_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;

    switch (ODF_arg->subIndex) {
        case 0 : // sub index size, uint8, readonly
            if(ODF_arg->reading) {
                uint8_t temp;
                ODF_arg->dataLength = sizeof(uint8_t);
                app_OD_read(ODF_arg->index, ODF_arg->subIndex, &temp, ODF_arg->dataLength);
                memcpy(ODF_arg->data, &temp, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case 1 : // selected daemon index in daemon list, uint8, readwrite

            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(list_index);
                memcpy(ODF_arg->data, &list_index, ODF_arg->dataLength);
            }
            else {
                if(ODF_arg->dataLength != sizeof(list_index)) {
                    log_error_ODF("app_manager_ODF", ODF_arg, "data size does not match");
                    ret = CO_SDO_AB_GENERAL; // error with data size
                    break;
                }
                memcpy(&list_index, ODF_arg->data, ODF_arg->dataLength);
            }

            break;

        case 2 : // app name, domain, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = strlen(daemon_list[list_index].name)+1;
                memcpy(ODF_arg->data, daemon_list[list_index].name, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case 3 : // daemon service name, domain, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = strlen(daemon_list[list_index].service_name)+1;
                memcpy(ODF_arg->data, daemon_list[list_index].service_name, ODF_arg->dataLength);
            }
            else
                return CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case 4 : // daemon current state, int32, readonly

            // TODO change to dbus call to systemd
            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(daemon_list[list_index].status);
                memcpy(ODF_arg->data, &daemon_list[list_index].status, ODF_arg->dataLength);
            }
            else
                return CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case 5 : // daemon change state, int32, writeonly

            if(ODF_arg->reading)
                return CO_SDO_AB_WRITEONLY; // can't read parameters, writeonly
            else {
                if(ODF_arg->dataLength != sizeof(daemon_list[list_index].status)) {
                    log_error_ODF("app_manager_ODF", ODF_arg, "data size does not match");
                    ret = CO_SDO_AB_GENERAL; // error with data size
                    break;
                }

                int32_t command;
                memcpy(&command, ODF_arg->data, ODF_arg->dataLength);
                if(command == START_DAEMON)
                     start_daemon(daemon_list[list_index].service_name);
                else if(command == STOP_DAEMON)
                    stop_daemon(daemon_list[list_index].service_name);
                else if(command == RESTART_DAEMON)
                    stop_daemon(daemon_list[list_index].service_name);
                else
                    log_error_ODF("app_manager_ODF", ODF_arg, "unkown input to daemon change state");
            }

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    return ret;
}


int
app_register_daemon(const char *name, const char *daemon_name) {
    uint8_t new_index;

    if(name == NULL || daemon_name == NULL || daemon_count > daemon_list_len)
        return -1; // invalid inputs or exceeded maxium daemons allowed

    pthread_mutex_lock(&dc_mutex);

    if(daemon_list == NULL) { // make daemon list
        daemon_count = 1;
        daemon_list = (daemon_data_t *)malloc(sizeof(daemon_data_t));
    }
    else { // add an daemon to existing daemon list
        ++daemon_count;
        daemon_list = (daemon_data_t *)realloc(daemon_list, sizeof(daemon_data_t) * daemon_count);
    }

    new_index = daemon_count - 1;

    // fill daemon data
    daemon_list[new_index].name = (char *)malloc(strlen(name)+1);
    strncpy(daemon_list[new_index].name, name, strlen(name)+1);
    daemon_list[new_index].service_name = (char *)malloc(strlen(daemon_name)+1);
    strncpy(daemon_list[new_index].service_name, daemon_name, strlen(daemon_name)+1);
    daemon_list[new_index].status = STOPPED;

    pthread_mutex_unlock(&dc_mutex);

    return new_index;
}


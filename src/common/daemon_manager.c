/**
 * Daemon manager for OreSat Linux Manager.
 *
 * @file        daemon_manager.c
 * @ingroup     daemon_manager
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#include "log_message.h"
#include "OD_helpers.h"
#include "log_message.h"
#include "dbus_controller.h"
#include "cpufreq.h"
#include "daemon_manager.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>


#ifndef DAEMON_LIST_ODF_INDEX
/** OD index for daemon list ODF */
#define DAEMON_LIST_ODF_INDEX           0x3004
#endif

#ifndef DAEMON_MANAGER_ODF_INDEX
/** OD index for daemon manager ODF */
#define DAEMON_MANAGER_ODF_INDEX        0x3005
#endif

/** Dbus destionation for systemd */
#define DESTINATION                     "org.freedesktop.systemd1"
/** Dbus interface name for systemd */
#define INTERFACE_NAME                  DESTINATION
/** Dbus object path for systemd */
#define OBJECT_PATH                     "/org.freedesktop/systemd1"

// ODF subindecies
#define DM_SI_SVC_SEL       1
#define DM_SI_APP_NAME      DM_SI_SVC_SEL+1
#define DM_SI_SVC_NAME      DM_SI_APP_NAME+1
#define DM_SI_SVC_CUR_STATE DM_SI_SVC_NAME+1
#define DM_SI_SVC_CHG_STATE DM_SI_SVC_CUR_STATE+1
#define DM_SI               DM_SI_SVC_CHG_STATE+1 // must be last


/**
 * Gobal for all apps to use to get acces to the OreSat Linux Manager's
 * dbus connetion. Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;


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


// see function definitions for doxygen comments
static int stop_daemon(char *daemon_name);
static int start_daemon(char *daemon_name);
static int restart_daemon(char *daemon_name);
static void save_power(void);

int
daemon_manager_setup() {
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
    uint8_t subindecies = DM_SI;

    switch (ODF_arg->subIndex) {
        case 0: // sub index size, uint8, readonly
            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(subindecies);
                memcpy(ODF_arg->data, &subindecies, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case DM_SI_SVC_SEL: // selected daemon index in daemon list, uint8, readwrite

            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(list_index);
                memcpy(ODF_arg->data, &list_index, ODF_arg->dataLength);
            }
            else {
                if(ODF_arg->dataLength != sizeof(list_index)) {
                    log_message(LOG_ERR, "daemon status data size does not match");
                    ret = CO_SDO_AB_GENERAL; // error with data size
                    break;
                }
                memcpy(&list_index, ODF_arg->data, ODF_arg->dataLength);
            }

            break;

        case DM_SI_APP_NAME: // app name, domain, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = strlen(daemon_list[list_index].name)+1;
                memcpy(ODF_arg->data, daemon_list[list_index].name, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case DM_SI_SVC_NAME: // daemon service name, domain, readonly

            if(ODF_arg->reading) {
                ODF_arg->dataLength = strlen(daemon_list[list_index].service_name)+1;
                memcpy(ODF_arg->data, daemon_list[list_index].service_name, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, readonly

            break;

        case DM_SI_SVC_CUR_STATE: // daemon current state, int32, readwrite

            // TODO change to dbus call to systemd
            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(daemon_list[list_index].status);
                memcpy(ODF_arg->data, &daemon_list[list_index].status, ODF_arg->dataLength);
            }
            else {
                if(ODF_arg->dataLength != sizeof(daemon_list[list_index].status)) {
                    log_message(LOG_ERR, "daemon status data size does not match");
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
                    restart_daemon(daemon_list[list_index].service_name);
                else
                    log_message(LOG_ERR, "unkown input to daemon change state");

                save_power();
            }

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    return ret;
}


/**
 * @brief Will try to start the daemon inputed.
 *
 * Wrapper for calling StartUnit on systemd dbus interface.
 * Equivalent to "systemctl start daemon_name"
 *
 * @param daemon_name The name of the daemon wanted to be started.
 *
 * @return 0 on sucess, negative on error
 */
static int
start_daemon(char *daemon_name) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r;

    r = sd_bus_call_method(
            APP_DBUS.bus,
            DESTINATION,
            OBJECT_PATH,
            INTERFACE_NAME,
            "StartUnit",
            &err,
            &mess,
            "ss",
            daemon_name,
            "fail");
    if (r < 0)
        log_message(LOG_ERR, "systemd method call StartUnit failed for %s", daemon_name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}


/**
 * @brief Will try to stop the daemon inputed.
 *
 * Wrapper for calling StopUnit on systemd dbus interface.
 * Equivalent to "systemctl stop daemon_name"
 *
 * @param daemon_name The name of the daemon wanted to be stopped.
 *
 * @return 0 on sucess, negative on error
 */
static int
stop_daemon(char *daemon_name) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r;

    r = sd_bus_call_method(
            APP_DBUS.bus,
            DESTINATION,
            OBJECT_PATH,
            INTERFACE_NAME,
            "StopUnit",
            &err,
            &mess,
            "ss",
            daemon_name,
            "fail");
    if (r < 0)
        log_message(LOG_ERR, "systemd method call StopUnit failed for %s", daemon_name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
}


/**
 * @brief Will try to restart the daemon inputed.
 *
 * Wrapper for calling RestartUnit on systemd dbus interface.
 * Equivalent to "systemctl restart daemon_name"
 *
 * @param daemon_name The name of the daemon wanted to be restarted.
 *
 * @return 0 on sucess, negative on error
 */
static int
restart_daemon(char *daemon_name) {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *mess = NULL;
    int r;

    r = sd_bus_call_method(
            APP_DBUS.bus,
            DESTINATION,
            OBJECT_PATH,
            INTERFACE_NAME,
            "RestartUnit",
            &err,
            &mess,
            "ss",
            daemon_name,
            "fail");
    if (r < 0)
        log_message(LOG_ERR, "systemd method call RestartUnit failed for %s", daemon_name);

    sd_bus_message_unref(mess);
    sd_bus_error_free(&err);
    return r;
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


/**
 * @breif Save power when no other OreSat daaemons are running.
 *
 * If all the daemon are stopped sets the cpufreq governor to powersave mode
 * or if any OreSat daemon is running sets the cpufreq governor to performance
 * mode.
 */
static void
save_power(void) {
    int cur_stop = 0;

    for(unsigned int i=0; i<daemon_count; ++i) {
        if(daemon_list[i].status ==  STOPPED)
            ++cur_stop;
    }

    if(cur_stop == 0)
        set_cpufreq_gov(powersave);
    else
        set_cpufreq_gov(performance);
}

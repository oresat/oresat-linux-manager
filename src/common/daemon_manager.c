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


#define PCRE2_CODE_UNIT_WIDTH       8 // must be set before including pcre2.h
#include <pcre2.h>


/** OD index for daemon list ODF */
#define DAEMON_LIST_ODF_INDEX       0x3001
/** OD index for daemon manager ODF */
#define DAEMON_MANAGER_ODF_INDEX    0x3002


/** List of data for daemons registered by apps */
static daemon_data_t *daemon_list = NULL;
/** Size of daemon list */
static uint8_t daemon_list_len = 0;
/** Number of daemon in dbus list */
static uint8_t daemon_count = 0;
/** Selected daemon index in daemon list */
static uint8_t list_index = 0;
/** Mutex for accesing data */
static pthread_mutex_t dc_mutex = PTHREAD_MUTEX_INITIALIZER;
/** List of file request struct that will be used when receiving files */
static recv_file_request_t *recv_file_request_list = NULL;
/** length of recv_file_request_list */
static int request_count = 0;


static bool match_regex(char *file_name, char *regex_string);


int
daemon_manager_setup() {
    // get the size of the daemon list in object dictionary
    app_OD_read(DAEMON_LIST_ODF_INDEX, 0, &daemon_list_len,sizeof(daemon_list_len));

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
        if(ODF_arg->subIndex == 0) {
            ODF_arg->dataLength = sizeof(daemon_list_len);
            memcpy(ODF_arg->data, &daemon_list_len, ODF_arg->dataLength);
        }
        else {
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


int
app_add_request_recv_file(
        char *app_name,
        char *regex_string,
        char *path_to_send,
        int (*recv_file_callback)(char *)) {

    int new_request = 0;

    // make sure inputs are valid
    if(app_name == NULL) {
        log_message(LOG_ERR, "add recv file request had no app name\n");
        return 0;
    }
    if(regex_string == NULL) {
        log_message(LOG_ERR, "app %s recv file request has no regex string\n", app_name);
        return 0;
    }
    if(path_to_send == NULL) {
        log_message(LOG_ERR, "app %s recv file request has no path\n", app_name);
        return 0;
    }
    if(path_to_send[0] != '/') {
        log_message(LOG_ERR, "app %s recv file request path is not an absolute path\n", app_name);
        return 0;
    }

    new_request = request_count;

    // add to request list
    if(request_count == 0) { // init request list
        request_count = 1;
        recv_file_request_list = (recv_file_request_t *)malloc(sizeof(recv_file_request_t));
    }
    else { // append to request list
        ++request_count;
        recv_file_request_list = (recv_file_request_t *)realloc(recv_file_request_list, sizeof(recv_file_request_t) * request_count);
    }

    // copy data
    recv_file_request_list[new_request].app_name = app_name;
    app_name = NULL;
    recv_file_request_list[new_request].regex_string = regex_string;
    regex_string = NULL;
    recv_file_request_list[new_request].path_to_send = path_to_send;
    path_to_send = NULL;
    recv_file_request_list[new_request].recv_file_callback = recv_file_callback;

    return 1;
}


static bool
match_regex(char *file_name, char *regex_string) {
    pcre2_code *re;
    PCRE2_SPTR pattern;
    PCRE2_SPTR subject;
    PCRE2_SIZE error_offset;
    pcre2_match_data *match_data;
    int error_number;
    size_t subject_length;
    bool rv = false;
    int r;

    pattern = (PCRE2_SPTR)regex_string;
    subject = (PCRE2_SPTR)file_name;
    subject_length = strlen((char *)subject);

    re = pcre2_compile(
            pattern,
            PCRE2_ZERO_TERMINATED,
            0,
            &error_number,
            &error_offset,
            NULL);

    if(re == NULL) { // compile failed
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(error_number, buffer, sizeof(buffer));
        log_message(LOG_ERR, "PCRE2 compilation failed at offset %d in %s\n", (int)error_offset, buffer);
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    // try to match regex
    r = pcre2_match(
            re,
            subject,
            subject_length,
            0,
            0,
            match_data,
            NULL);

    if(r > 0) // regex matched
        rv = true;

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);

    return rv;
}

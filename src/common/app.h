#ifndef APP_H
#define APP_H

#include "app_OD_helpers.h"

/**
 * Call this function to register an app for the candameon to controll.
 *
 * @param: name is the app name
 * @param: daemon_name is the daemon service name (ie: oresat-gps.service). Set
 * this to NULL if there is no daemon to controll.
 * @param: thread_main is the app main function. Set this to NULL if there is
 * no needed for a seperate thread for the app.
 *
 * @return: the index if the array, if registered correctly or a negative value on error.
 */
int app_register(
        const char *name,
        const char *daemon_name,
        int (*thread_main)(void));


/**
 *
 */
CO_SDO_abortCode_t app_controller_ODF(CO_ODF_arg_t *ODF_arg);


#endif

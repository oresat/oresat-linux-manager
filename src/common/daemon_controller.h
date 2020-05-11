#ifndef APP_DAEMON_CONTROLLER_H
#define APP_DAEMON_CONTROLLER_H


#include "app_OD_helpers.h"


enum daemon_states {
    failed = 0,
    running = 1,
    stopped = 2,
};


/**
 * Call this function to register an app for the candameon to controll.
 *
 * @param: name is the app name
 * @param: daemon_name is the daemon service name (ie: oresat-gpsd.service). Set
 * this to NULL if there is no daemon to controll.
 * @param: thead main is the app main function to set up the dbus client that
 * will be given it own thread. Set this to NULL if there is no needed for a
 * seperate dbus thread for the app.
 *
 * @return: the index if the array, if registered correctly or a negative value on error.
 */
int app_register_daemon(const char *name, const char *daemon_name);


/**
 * Object Dictionary Function for app/daemon contoller.
 */
CO_SDO_abortCode_t daemon_controller_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * Used to stop all apps dbus threads in apps list. Ment to be used when
 * candaemon is exiting.
 *
 * @return: # of apps ended or negative on error.
 */
int end_apps();


#endif

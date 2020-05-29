/**
 * Daemon controller for CANdaemon.
 *
 * @file        daemon_controller.h
 * @ingroup     daemon_controller
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https//github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef APP_DAEMON_CONTROLLER_H
#define APP_DAEMON_CONTROLLER_H


#include "app_OD_helpers.h"


/**
 * @ingroup candaemon_general
 * @defgroup daemon_controller Daemon Controller
 * @{
 *
 * Allows the CANdameon to control any daemon requested by an app.
 */


/**
 * States the daemon could be in
 */
enum daemon_states {
    /** daemon has stop running and has failed */
    failed = 0,
    /** daemon is currently running */
    running = 1,
    /** daemon has stopped */
    stopped = 2,
};


/**
 * Object Dictionary Function for app/daemon contoller.
 *
 * @param Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t daemon_controller_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * Used to stop all apps dbus threads in apps list. Ment to be used when
 * candaemon is exiting.
 *
 * @return # of apps ended or negative on error.
 */
int end_apps();

/** @} */


/**
 * @ingroup App_Helpers
 * @{
 *
 * Allow the CANdaemon to controll any daemon register by an app.
 */


/**
 * Call this function to register an app for the candameon to controll.
 *
 * @param name is the app name
 * @param daemon_name is the daemon service name (ie oresat-gpsd.service). Set
 * this to NULL if there is no daemon to controll.
 *
 * @return the index if the array, if registered correctly or a negative value on error.
 */
int app_register_daemon(const char *name, const char *daemon_name);

/** @} */
#endif

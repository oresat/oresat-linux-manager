/**
 * Daemon manager for OLM.
 *
 * @file        daemon_manager.h
 * @ingroup     daemon_manager
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef DAEMON_MANAGER_H
#define DAEMON_MANAGER_H


#include "CANopen.h"
#include <stdint.h>
#include <stdbool.h>


/**
 * @defgroup daemon_manager Daemon Manager
 * @{
 *
 * Allows the CANdameon to control any daemon requested by an app.
 *
 * ### Daemon list OD entry
 * | Sub Index | Usage                         | Data Type   | Access   |
 * | :-------- | :---------------------------: | :---------: | :------: |
 * |     0     | Number of subindex in record  | uint8       | readonly |
 * |     1     | App name 1                    | DOMAIN      | readonly |
 * |    ...    | ...                           | DOMAIN      | readonly |
 * |    127    | App name 127                  | DOMAIN      | readonly |
 *
 *
 *  ### Daemon manager OD entry
 *  | Sub Index | Usage                             | Data Type | Access    |
 *  | :-------- | :-------------------------------: | :-------: | :-------: |
 *  |     0     | Number of subindex in record      | uint8     | readonly  |
 *  |     1     | Current index in app list array   | uint8     | readwrite |
 *  |     2     | App name                          | DOMAIN    | readonly  |
 *  |     3     | Daemon service name               | DOMAIN    | readonly  |
 *  |     4     | Daemon current state              | int32     | readonly  |
 *  |     5     | Daemon change state               | int32     | readwrite |
 *
 *  ### How the daemon contoller OD entries work:
 *  - CAN Master node can set subindex 1 (app list index) with the index of the app wanted form the app list. Updating that index will load all other subidexes with the that app info.
 *  - subindex 2: App's name.
 *  - subindex 3: Daemon service name.
 *  - subindex 4: Daemon current state 0 running, 1 for stopped, 2 for error.
 *  - subindex 5: Change daemon's state 0 start/restart, 1 for stop.
 */


/**
 * Holds all of an app daemon data.
 * Filled by app_register() and used by the app_manager_ODF().
 */
typedef struct {
    /** App's name */
    char *name;
    /** Service name for daemon associate with app */
    char *service_name;
    /** Status of the daemon associate with app */
    int32_t status;
} daemon_data_t;


/**
 * States the daemon could be in.
 */
enum daemon_states {
    /** Daemon has stop running and has failed */
    FAILED = 0,
    /** Daemon is currently running */
    RUNNING = 1,
    /** Daemon has stopped */
    STOPPED = 2,
};


/**
 * Systemd commands for daemons.
 */
enum daemon_commands {
    /** Stop the daemon */
    STOP_DAEMON = 0,
    /** Start the daemon */
    START_DAEMON = 1,
    /** Restart the daemon */
    RESTART_DAEMON = 2,
};


/**
 * Nice function to setup the daemon manager ODFs.
 *
 * @return 0 on sucess
 */
int daemon_manager_setup();


/**
 * Object Dictionary Function for daemon list OD entry.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t daemon_list_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * Object Dictionary Function for daemon contoller OD entry.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t daemon_manager_ODF(CO_ODF_arg_t *ODF_arg);


/** @} */


/**
 * @ingroup App_Helpers
 * @{
 *
 * Allow the OLM to controll any daemon register by an app.
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

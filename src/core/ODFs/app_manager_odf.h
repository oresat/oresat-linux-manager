/**
 * App Manager ODF.
 *
 * @file        app_manager_odf.h
 * @ingroup     app_manager_odf
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for apps running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef APP_MANAGER_ODF_H
#define APP_MANAGER_ODF_H

#include "CANopen.h"

/** Systemd commands for apps. */
enum unit_commands {
    /** Stop the apps's unit. */
    STOP_DAEMON = 0,
    /** Start the app's unit. */
    START_DAEMON = 1,
    /** Restart the app's unit. */
    RESTART_DAEMON = 2,
};

/**
 * Object Dictionary Function for app contoller OD entry.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t app_manager_ODF(CO_ODF_arg_t *ODF_arg);

#endif /* APP_MANAGER_ODF_H */

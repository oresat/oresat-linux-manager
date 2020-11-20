/**
 * App for interfacing with systemd power setting.
 *
 * @file        logind_interface.h
 * @ingroup     logind_interface
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef LOGIND_APP_H
#define LOGIND_APP_H


#include "app_include.h"

/**
 * @ingroup     system_apps
 * @defgroup    power_management_app Power managment app
 * @{
 *
 * System app that can use systemd power options.
 */


/**
 * @brief Nice function for call all function needed for linux updater app.
 *
 * @return Negative errno number on error
 */
int logind_app_setup();


/**
 * Give the CAN network manager control over board's power settings
 * (issue poweroff and reboot).
 *
 * @param ODF_arg Pointer to the current SDO ODF arguments
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t logind_ODF(CO_ODF_arg_t *ODF_arg);


/** @} */
#endif

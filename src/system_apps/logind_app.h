/**
 * App for interfacing with systemd power setting.
 *
 * @file        logind_app.h
 * @ingroup     logind_app
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
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
 * Give the candaemon / CAN network manager control over board's power settings
 * (issue poweroff and reboot).
 *
 * @param ODF_arg Pointer to the current SDO ODF arguments
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t logind_ODF(CO_ODF_arg_t *ODF_arg);


/** @} */
#endif

/**
 * App for interfacing with systemd power setting.
 *
 * @file        power_management_app.h
 * @ingroup     power_management_app
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H


/**
 * @ingroup     system_apps
 * @defgroup    power_management_app Power managment app
 * @{
 *
 * System app that can use systemd power options.
 */


#include "CANopen.h"


/**
 * Give the candaemon / CAN network manager control over board's power settings
 * (issue poweroff and reboot).
 *
 * @param ODF_arg Pointer to the current SDO ODF arguments
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t power_management_ODF(CO_ODF_arg_t *ODF_arg);


/** @} */
#endif

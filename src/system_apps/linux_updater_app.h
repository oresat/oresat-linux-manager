/**
 * App for the Linux updater dameon.
 *
 * @file        linux_updater_app.h
 * @ingroup     linux_updater_app
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef UPDATER_APP_H
#define UPDATER_APP_H


#include "CANopen.h"
#include <systemd/sd-bus.h>
#include <pthread.h>


/**
 * @ingroup     system_apps
 * @defgroup    linux_updater_app OreSat Linux updater app
 * @{
 *
 * System app that communicates with the OreSat Linux updater daemon.
 *
 * See <https://github.com/oresat/oresat-linux-updater> for info on the daemon.
 */


/**
 * @brief Nice function for registering all dbus signal matches for the linux updater.
 *
 * @return Negative errno number on error
 */
int linux_updater_dbus_signal_match(void);


/**
 * @brief ODF callback for getting the linux updater's ODF.
 *
 * @param ODF_arg Pointer to the current SDO ODF arguments
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t updater_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * @brief DBus callback for reading the emit when changes signal.
 *
 * @param m Pointer to raw dbus message
 * @param userdata Pointer to optional userdata that was register with callback
 * @param ret_error ret error that can be set on when callback errors
 *
 * @return negative errno number on error
 */
int read_status_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);


/** @} */
#endif

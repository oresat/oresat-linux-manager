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
 * See the [oresat-linux-updater repo](https://github.com/oresat/oresat-linux-updater)
 * for info the the Linux Updater Daemon.

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
 * **Subindex of OD index:**
 * | Sub Index | Usage                             | Data Type     | Access    |
 * | :-------: | :-------------------------------: | :-----------: | :-------: |
 * |     0     | Number of subindex in record      | uint8         | readonly  |
 * |     1     | Update Status                     | uint8         | readonly  |
 * |     2     | Current File                      | DOMAIN        | readonly  |
 * |     3     | Updates Available                 | uint32        | readonly  |
 * |     4     | Add Update File                   | DOMAIN        | writeonly |
 * |     5     | Update Now                        | boolean       | writeonly |
 * |     6     | Stop Update                       | boolean       | writeonly |
 * |     7     | Delete Current File               | boolean       | writeonly |
 *
 * **How updates work:**
 *  - The master CAN node can write in the paths to an update tar file for the updater to run in subindex 4. The updater will not run those updates until a boolean is written into subindex 5; at which point the updater will start or continue an update. If the master node need updater to stop, it can write a boolean to subindex 6.
 *  - Subindex 1 is the current/last update status (negative for error, 0 for sleeping, 1 for updating, 2 for stopped).
 *  - Subindex 2 and 3 is just useful information.
 *  - Subindex 7 is for delete the update current update file in subindex 2 an any temp files make from uncompressed.
 *
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

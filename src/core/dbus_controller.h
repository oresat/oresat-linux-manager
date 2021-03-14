/**
 * The dbus controller for all apps.
 *
 * @file        dbus_controller.h
 * @ingroup     dbus_controller
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef DBUS_CONTROLLER_H
#define DBUS_CONTROLLER_H

#include "olm_app.h"
#include <systemd/sd-bus.h>
#include <stdbool.h>


/**
 * @defgroup dbus_controller DBus Controller
 * @{
 *
 * Centralize dbus connection for all apps.
 *
 * All apps that need access to a dbus connection will share the same dbus
 * client connection thru the app_dbus_controller.
 */


/**
 * Status on dbus connection
 *
 * Only dbus controller functions should write
 * All apps can read from the gobal defined in app_dbus_controller.c
 * */
typedef struct {
    /** pointer to app dbus connection */
    sd_bus *bus;
    /** status dbus loop */
    bool loop_running;
} dbus_data_t;


/**
 * Initialize the app dbus connection.
 *
 * @return >= 0 on success, < 0 on failure
 */
int dbus_controller_init(void);


/**
 * A loop waiting for dbus signal that were register by app on the app dbus connection.
 *
 * Expected to be given its own thread.
 *
 * @return 0 on sucess
 */
int dbus_controller_loop(void);


/**
 * Ends the app dbus connection.
 *
 * @return 0 on sucess
 */
int dbus_controller_end(void);


/** @} */
#endif

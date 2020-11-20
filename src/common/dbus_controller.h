/**
 * The dbus controller for all apps.
 *
 * @file        dbus_controller.h
 * @ingroup     dbus_controller
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef DBUS_CONTROLLER_H
#define DBUS_CONTROLLER_H


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
int dbus_controller_init();


/**
 * Setup all app that will use dbus connection.
 *
 * Wrapper function to call system_apps_setup() and board_apps_setup()
 *
 * @return number of apps added
 */
int dbus_controller_setup_apps();


/**
 * A loop waiting for dbus signal that were register by app on the app dbus connection.
 *
 * Expected to be given its own thread.
 *
 * @return 0 on sucess
 */
int dbus_controller_loop();


/**
 * Ends the app dbus connection.
 *
 * @return 0 on sucess
 */
int dbus_controller_end();


/** @} */
#endif

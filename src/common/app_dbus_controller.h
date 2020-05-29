/**
 * The dbus controller for all apps.
 *
 * @file        app_dbus_controller.h
 * @ingroup     app_dbus_controller
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */

#ifndef APP_DBUS_CONTROLLER_H
#define APP_DBUS_CONTROLLER_H

#include <systemd/sd-bus.h>
#include <stdbool.h>


typedef struct {
    /** pointer to app dbus connection */
    sd_bus *bus;
    /** status dbus loop */
    bool loop_running;
} app_dbus_data_t;


/**
 * Reset CAN interface and set to listen only mode
 *
 * @return >= 0 on success, < 0 on failure
 */
int apps_dbus_start();


/**
 * The main function loop for dbus inteface.
 *
 * Should be given it own thread.
 *
 * @return 1 on sucess
 */
int apps_dbus_main();


/**
 * Starts the dbus interface
 *
 * @return 1 on sucess
 */
int apps_dbus_end();

#endif

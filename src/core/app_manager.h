/**
 * The OLM app manager.
 *
 * @file        app_manager.h
 * @ingroup     app_manager
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include "olm_app.h"
#include <systemd/sd-bus.h>
#include <stdbool.h>

/**
 * @defgroup app_manager DBus Controller
 * @{
 *
 * Centralize dbus connection for all apps.
 *
 * All apps that need access to a dbus connection will share the same dbus
 * client connection thru the app_app_manager.
 */

/**
 * Status on dbus connection
 *
 * Only dbus controller functions should write
 * All apps can read from the gobal defined in app_app_manager.c
 * */
typedef struct {
    /** pointer to app dbus connection */
    sd_bus *bus;
} dbus_data_t;

/**
 * A loop waiting for dbus signal that were register by app on the app dbus
 * connection.
 */
void app_manager_dbus_run(void);

/** @} */
#endif /* APP_MANAGER_H */

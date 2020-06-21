/**
 * Systemd app for CANdaemon, that allow it to control daemons using dbus.
 *
 * @file        systemd_app.h
 * @ingroup     systemd_app
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https//github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef SYSTEMD_APP_H
#define SYSTEMD_APP_H


#include "app_include.h"


/**
 * @ingroup     system_apps
 * @defgroup    systemd_app Systemd App
 * @{
 *
 * A System app to provide a interface to systemd over dbus.
 */


/**
 * @brief Nice function for call all function needed for daemon controller app.
 *
 * @return 1 on success
 */
int systemd_app_setup();


/**
 * @brief Will try to start the daemon inputed.
 *
 * Wrapper for calling StartUnit on systemd dbus interface.
 * Equivalent to "systemctl start daemon_name"
 *
 * @param daemon_name The name of the daemon wanted to be started.
 *
 * @return 0 on sucess, negative on error
 */
int start_daemon(char *daemon_name);


/**
 * @brief Will try to stop the daemon inputed.
 *
 * Wrapper for calling StopUnit on systemd dbus interface.
 * Equivalent to "systemctl stop daemon_name"
 *
 * @param daemon_name The name of the daemon wanted to be stopped.
 *
 * @return 0 on sucess, negative on error
 */
int stop_daemon(char *daemon_name);


/**
 * @brief Will try to restart the daemon inputed.
 *
 * Wrapper for calling RestartUnit on systemd dbus interface.
 * Equivalent to "systemctl restart daemon_name"
 *
 * @param daemon_name The name of the daemon wanted to be restarted.
 *
 * @return 0 on sucess, negative on error
 */
int restart_daemon(char *daemon_name);


/** @} */
#endif

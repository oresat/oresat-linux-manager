/**
 * Systemd app.
 *
 * @file        systemd_app.h
 * @ingroup     systemd_app
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef SYSTEMD_APP_H
#define SYSTEMD_APP_H

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
int stop_daemon(char *daemon_name);

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
int start_daemon(char *daemon_name);

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

#endif /* SYSTEMD_APP_H */

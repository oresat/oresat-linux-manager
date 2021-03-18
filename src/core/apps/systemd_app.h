/**
 * The app for interfacing with systemd over D-Bus.
 *
 * @file        systemd_app.h
 * @ingroup     core_apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef SYSTEMD_APP_H
#define SYSTEMD_APP_H

enum active_states {
    active = 0,
    reloading = 1,
    inactive = 2,
    failed = 3, 
    activating = 4,
    deactivating = 5,
};

/**
 * @brief Get the systemd unit object path for a unit.
 *
 * @param name The name of the unit.
 *
 * @return The unit object path that must be freed with free() or NULL on
 * error.
 */
char *get_unit(const char *name);

/**
 * @brief Start a systemd unit.
 *
 * @param unit The object path for unit to be started.
 *
 * @return A postive interger on success or negative errno value on error.
 */
int start_unit(const char *unit);

/**
 * @brief Stop a systemd unit.
 *
 * @param unit The object path of the unit to be stopped.
 *
 * @return A postive interger on success or negative errno value on error.
 */
int stop_unit(const char *unit);

/**
 * @brief Restart a systemd unit.
 *
 * @param unit The object path for the unit to be restarted.
 *
 * @return A postive interger on success or negative errno value on error.
 */
int restart_unit(const char *unit);

/**
 * @brief Gets the active state of a systemd unit.
 *
 * @param unit The unit object path to get the active state of.
 *
 * @return A @ref active_states value on success or negative on error.
 */
int get_active_state_unit(const char *unit);

#endif /* SYSTEMD_APP_H */

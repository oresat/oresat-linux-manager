/**
 * Module for interfacing with Systemd over D-Bus.
 *
 * @file        systemd.c
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef SYSTEMD_MODULE_H
#define SYSTEMD_MODULE_H

#include "olm_app.h"

/**
 * @brief Get the systemd unit object path for a unit.
 *
 * @param name The name of the unit.
 *
 * @return The unit object path that must be freed with free() or NULL on
 * error.
 */
char *
get_unit(const char *name);

/**
 * @brief Get the systemd unit object path for a unit if not loaded.
 *
 * @param name The name of the unit.
 *
 * @return The unit object path that must be freed with free() or NULL on
 * error.
 */
char *
load_unit(const char *name);

/**
 * @brief Start a systemd unit.
 *
 * @param unit The object path for unit to be started.
 *
 * @return A postive interger on success or negative errno value on error.
 */
int
start_unit(const char *unit);

/**
 * @brief Stop a systemd unit.
 *
 * @param unit The object path of the unit to be stopped.
 *
 * @return A postive interger on success or negative errno value on error.
 */
int
stop_unit(const char *unit);

/**
 * @brief Restart a systemd unit.
 *
 * @param unit The object path for the unit to be restarted.
 *
 * @return A postive interger on success or negative errno value on error.
 */
int
restart_unit(const char *unit);

/**
 * @brief Gets the active state of a systemd unit.
 *
 * @param unit The unit object path to get the active state of.
 *
 * @return A @ref active_states value.
 */
unit_active_states_t
get_unit_active_state(const char *unit);

#endif /* SYSTEMD_MODULE_H */

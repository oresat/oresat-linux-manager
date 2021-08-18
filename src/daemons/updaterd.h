/**
 * Module for interfacing with the OreSat Linux Updater daemon over D-Bus.
 *
 * @file        updater.h
 * @ingroup     daemons
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef UPDATER_MODULE_H
#define UPDATER_MODULE_H

#include <stdbool.h>
#include <stdint.h>

#define UPDATER_SERVICE_FILE "oresat-linux-updaterd.service"

/**
 * @brief Give the OreSat Linux Updater daemon a new update archive. The
 * updater will copy the file.
 *
 * @param file The absolute path to the file.
 *
 * @return 1 if the file was added, 0 on if it wasn't, negativer errno on
 * error.
 */
int
updaterd_add_update_archive(const char *file);

/**
 * @brief Tells the Updater to update.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int
updaterd_update(void);

/**
 * @brief Tells the OreSat Linux Updater to make a status archive.
 *
 * @param out The absolute path to the file. String must be freed with free()
 * when no longer needed.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int
updaterd_make_status_archive(char **out);

/**
 * @breif Gets the status enum.
 *
 * @param state The value to set.
 *
 * @return 0 on sucess or a negative errno value on error.
 */
int
updaterd_status(uint8_t *state);

/**
 * @breif Gets the number of updates available.
 *
 * @param count The value to set.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int
updaterd_updates_available(uint32_t *count);

/**
 * @breif Gets the list of updates.
 *
 * @param out The list of updates string as a JSON str on sucess. String must
 * be freed with free() when no longer needed.
 *
 * @return non negative number on sucess or negativer errno on error.
 */
int
updaterd_list_updates(char **out);

#endif /* UPDATER_MODULE_H */

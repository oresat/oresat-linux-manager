/**
 * OreSat Linux Updater daemon app.
 *
 * @file        updater_app.h
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef UPDATER_APP_H
#define UPDATER_APP_H

#include "olm_file_cache.h"
#include "olm_app.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Make the linux updater app.
 *
 * @return negative errno value on error.
 */
int updater_app(olm_app_t *app);

/**
 * @brief Give the OreSat Linux Updater daemon a new update archive. The
 * updater will copy the file.
 *
 * @param file The absolute path to the file.
 *
 * @return 1 if the file was added, 0 on if it wasn't, negativer errno on
 * error.
 */
int updater_app_add_update_archive(const char *file);

/**
 * @brief Tells the Updater to update.
 *
 * @return 0 on sucess or negativer errno  on error.
 */
int updater_app_update(void);

/**
 * @brief Tells the OreSat Linux Updater to make a status archive.
 *
 * @param file The absolute path to the file.
 *
 * @return 0 on sucess or negativer errno  on error.
 */
int updater_app_make_status_archive(void);

/**
 * @breif Gets the status enum.
 * 
 * @param state The value to set.
 *
 * @return 0 on sucess or a negative errno value on error.
 */
int updater_app_status(uint8_t *state);

/**
 * @breif Gets the number of updates available.
 * 
 * @param count The value to set.
 *
 * @return 0 on sucess or a negative errno value on error.
 */
int updater_app_updates_available(uint32_t *count);

/**
 * @breif Gets the list of updates.
 *
 * @param out The list of updates string.
 * 
 * @return list of updates a JSON str on sucess or NULL on error. String must
 * be freed with free() when no longer needed.
 */
int updater_app_list_updates(char **out);

#endif /* UPDATER_APP_H */
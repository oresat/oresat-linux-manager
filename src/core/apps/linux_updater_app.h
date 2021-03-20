/**
 * OreSat Linux Updater daemon app.
 *
 * @file        linux_updater_app.h
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef UPDATER_APP_H
#define UPDATER_APP_H

#include "olm_app.h"
#include <stdint.h>
#include <stdbool.h>

int linux_updater_app(olm_app_t *app);
uint32_t linux_updater_updates_available(void);
int linux_updater_app_add_update_file(const char *file);
bool linux_updater_start_update(void);
bool linux_updater_stop_update(void);
bool linux_updater_reset(void);
bool get_apt_list_output(void);

#endif /* UPDATER_APP_H */

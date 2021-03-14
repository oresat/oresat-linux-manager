/**
 * Template app.
 *
 * @file        template_app.h
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef TEMPLATE_APP_H
#define TEMPLATE_APP_H

#include "olm_app.h"

olm_app_t* linux_updater_app_create(void);
int template_app_fwrite_file(const char *file);

#endif /* TEMPLATE_APP_H */

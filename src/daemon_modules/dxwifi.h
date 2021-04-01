/**
 * Module for interfacing with the OreSat DxWiFi daemon over D-Bus.
 *
 * @file        dxwifi.h
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef DXWIFI_MODULE_H
#define DXWIFI_MODULE_H

#include "olm_app.h"

void dxwifi_app(olm_app_t *app);

#endif /* DXWIFI_MODULE_H */

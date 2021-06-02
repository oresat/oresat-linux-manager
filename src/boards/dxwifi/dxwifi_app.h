/**
 * OreSat DxWiFi app.
 *
 * @file        dxwifi_app.h
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef DXWIFI_APP_H
#define DXWIFI_APP_H

#include "olm_file_cache.h"

void
dxwifi_app_async(void *data, olm_file_cache_t *fread_cache);

void
dxwifi_app_end(void *data);

#endif /* DXWIFI_APP_H */

/**
 * OreSat DxWiFi app.
 *
 * @file        dxwifi_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "dxwifi_app.h"
#include "CANopen.h"
#include "olm_file_cache.h"
#include <stdbool.h>

#define TPDO_DXWIFI 2

void
dxwifi_app_async(void *data, olm_file_cache_t *fread_cache) {
    CO_LOCK_OD();
    CO->TPDO[TPDO_DXWIFI]->valid = true;
    OD_dxWiFiStatus              = true;
    CO_UNLOCK_OD();
}

void
dxwifi_app_end(void *data) {
    CO_LOCK_OD();
    CO->TPDO[TPDO_DXWIFI]->valid = false;
    OD_dxWiFiStatus              = false;
    CO_UNLOCK_OD();
}

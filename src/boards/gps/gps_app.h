/**
 * OreSat GPS app.
 *
 * @file        gps_app.h
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef GPS_APP_H
#define GPS_APP_H

#include "olm_file_cache.h"

void gps_app_async(void *data, olm_file_cache_t *fread_cache);

void gps_app_end(void *data);

#endif /* GPS_APP_H */

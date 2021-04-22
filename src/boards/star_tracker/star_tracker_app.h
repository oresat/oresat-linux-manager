/**
 * OreSat Star Tracker app.
 *
 * @file        star_tracker_app.h
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef STAR_TRACKER_APP_H
#define STAR_TRACKER_APP_H

#include "olm_file_cache.h"
#include "star_tracker.h"

void star_tracker_app_async(void *data, olm_file_cache_t *fread_cache);

void star_tracker_app_end(void *data);

#endif /* STAR_TRACKER_APP_H */

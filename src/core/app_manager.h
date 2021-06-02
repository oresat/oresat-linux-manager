/**
 * OLM app manager.
 *
 * @file        app_manager_odf.h
 * @ingroup     app_manager_odf
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for apps running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include "CANopen.h"
#include "board_main.h"
#include "olm_app.h"
#include <stdbool.h>

/**
 * @breif Initalize all the systemd1 object paths in the daemon apps list.
 *
 * @param app_manager Daemon apps list.
 *
 * @return 1 on success or negative errno on failure.
 */
int
app_manager_init(olm_app_t **apps);

/**
 * @breif App Manager function to be called in the async thread/loop.
 *
 * @param apps The daemon app list.
 * @param fwrite_cache The file write cache.
 */
void
app_manager_async(olm_app_t **apps, olm_file_cache_t *fwrite_cache);

/** Object Dictionary Function for App Manager OD entry. */
CO_SDO_abortCode_t
app_manager_ODF(CO_ODF_arg_t *arg);

#endif /* APP_MANAGER_H */

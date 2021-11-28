/**
 * OreSat Linux Updater dameon app.
 *
 * @file        updater_odf.h
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef UPDATER_ODF_H
#define UPDATER_ODF_H

#include "CANopen.h"
#include "olm_file_cache.h"

void updater_async(void *data, olm_file_cache_t *fread_cache);

void updater_end(void *data);

CO_SDO_abortCode_t updater_ODF(CO_ODF_arg_t *ODF_arg);

#endif

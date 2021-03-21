/**
 * OLM Globals.
 *
 * @file        globals.c
 * @ingroup     globals
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include "olm_app.h"
#include "olm_file_cache.h"
#include <systemd/sd-bus.h>

/** List of OLM apps. Defined in board_main.c */
extern olm_app_t *apps;

/**
 * File cache for files that can be read over the CANbus by the Network
 * Manager. Defined in main.c
 */
extern olm_file_cache_t *fread_cache;

/**
 * File cache for files that were written over the CANbus by the Network
 * Manager. Defined in main.c
 */
extern olm_file_cache_t *fwrite_cache;

/** System D-Bus connection. Defined in main.c */
extern sd_bus *system_bus;

#endif /* GLOBALS_H */

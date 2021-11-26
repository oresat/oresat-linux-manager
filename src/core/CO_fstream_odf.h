/**
 * Reading/writing files over CAN ODF (Object Dictionary Function).
 *
 * @file        CO_file_transfer.h
 * @ingroup     file_transfer
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef _CO_FILE_TRANSFER_H_
#define _CO_FILE_TRANSFER_H_

#include "CANopen.h"
#include "olm_file.h"
#include "olm_file_cache.h"
#include <stdint.h>
#include <stdio.h>

/** fread / fwrite ODF private data */
typedef struct {
    /** The temp directory to read files in to or write files into. */
    const char *dir;
    /** The file cahe to use. */
    olm_file_cache_t *cache;
    /** The name of file selected. */
    char *file;
    /** Pointer to file being sent currently. */
    FILE *fptr;
    /** The progess of file transfer. */
} CO_fstream_t;

#define CO_FSTREAM_INITALIZER(_dir, _cache)                                    \
    { .dir = _dir, .cache = _cache, .file = NULL, .fptr = NULL, }

/**
 * @brief Reset all CO_fstream data, including closing any opened files.
 *
 * @param data The data to cleanup.
 */
void CO_fstream_reset(CO_fstream_t *data);

/**
 * @brief Callback for using inside CO_OD_configure() function for reading
 * files from object dictionary. When add with @ref CO_OD_configure, a
 * CO_fstream_t object must be pass into the object arguemnt.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t CO_fread_ODF(CO_ODF_arg_t *ODF_arg);

/**
 * @brief Callback for using inside CO_OD_configure() function for writing
 * files from object dictionary. When add with @ref CO_OD_configure, a
 * CO_fstream_t object must be pass into the object arguemnt.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t CO_fwrite_ODF(CO_ODF_arg_t *ODF_arg);

#endif /* _CO_FILE_TRANSFER_H_ */

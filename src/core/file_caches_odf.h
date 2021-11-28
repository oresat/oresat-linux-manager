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

#ifndef FILE_CACHES_ODF_H
#define FILE_CACHES_ODF_H

#include "CANopen.h"
#include "olm_file.h"
#include "olm_file_cache.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define FREAD_CACHE  0
#define FWRITE_CACHE 1

/** file transfer caches ODF private data. */
typedef struct {
    /** The file cache for files to be read from the Linux board */
    olm_file_cache_t *fread_cache;
    /** The file cache for files written to the Linux board */
    olm_file_cache_t *fwrite_cache;
    /** The current filter, will be NULL for no filter. */
    char *keyword;
} file_caches_t;

#define FILE_CACHES_INTIALIZER(_fread_cache, _fwrite_cache)                    \
    {                                                                          \
        .fread_cache = _fread_cache, .fwrite_cache = _fwrite_cache,            \
        .keyword = NULL,                                                       \
    }

void file_caches_free(file_caches_t *caches);

/**
 * @brief ODF for list all file in the read and write caches and modifing the
 * caches. A file_caches_t object must be passed into the object arguemnt for
 * CO_OD_configure when adding this ODF.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t file_caches_ODF(CO_ODF_arg_t *ODF_arg);

#endif /* FILE_CACHES_ODF_H */

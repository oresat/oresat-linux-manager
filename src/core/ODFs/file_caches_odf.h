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
#include "CO_driver.h"
#include "olm_file.h"
#include <stdint.h>
#include <stdio.h>

#ifndef FREAD_TMP_DIR
#define FREAD_TMP_DIR           "/tmp/olm-fread/"
#endif /* FREAD_TMP_DIR */

#ifndef FWRITE_TMP_DIR
#define FWRITE_TMP_DIR          "/tmp/olm-fwrite/"
#endif /* FWRITE_TMP_DIR */

#ifndef FREAD_CACHE_DIR
#define FREAD_CACHE_DIR         "/var/lib/oresat-linux-manager/read/"
#endif /* FREAD_CACHE_DIR */

#ifndef FWRITE_CACHE_DIR
#define FWRITE_CACHE_DIR        "/var/lib/oresat-linux-manager/write/"
#endif /* FWRITE_CACHE_DIR */

#define READ_CACHE 0
#define WRITE_CACHE 1

/** fread / fwrite ODF private data */
typedef struct {
    /** The temp directory to read files in to or write files into. */
    const char *dir;
    /** The name of file selected. */
    char *file;
    /** Pointer to file being sent currently. */
    FILE *fptr;
    /** The progess of file transfer. */
    uint32_t bytes_transfered;
} file_io_t;

/** file transfer caches ODF private data. */
typedef struct {
    /** The cache selected, must be set to READ_CACHE or WRITE_CACHE. */
    uint8_t selector;
    /** The current filter, will be NULL for no filter. */
    char *keyword;
    /**
     * The current index in file list selected, will be zero when cache is
     * empty.
     */
    uint32_t iterator;
} file_caches_t;

/** All file transfer ODF private data */
typedef struct {
    file_io_t fread;
    file_io_t fwrite;
    file_caches_t caches;
} file_transfer_t;

#define FILE_TRANSFER_INITIALIZER { \
    .fread = { \
        .dir = FREAD_TMP_DIR, \
        .file = NULL, \
        .fptr = NULL, \
        .bytes_transfered = 0, \
    }, \
    .fwrite = { \
        .dir = FWRITE_TMP_DIR, \
        .file = NULL, \
        .fptr = NULL, \
        .bytes_transfered = 0, \
    }, \
    .caches = { \
        .selector = READ_CACHE, \
        .keyword = NULL, \
        .iterator = 0, \
    }, \
}

/**
 * @brief Configure all application OD functions and setup file transfer cache.
 *
 * @return 0 on success
 */
int file_transfer_ODF_init(void);

/**
 * @brief Clean up all file transfer data, including closing any opened files.
 *
 * @return 0 on success or negative errno on error
 */
int file_transfer_ODF_end(void);

/**
 * @brief Callback for using inside CO_OD_configure() function for reading
 * files from object dictionary.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t fread_ODF(CO_ODF_arg_t *ODF_arg);

/**
 * @brief Callback for using inside CO_OD_configure() function for writing
 * files from object dictionary.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t fwrite_ODF(CO_ODF_arg_t *ODF_arg);

/**
 * @brief ODF for list all file in the read and write caches and modifing the
 * caches.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t file_caches_ODF(CO_ODF_arg_t *ODF_arg);

#endif /* _CO_FILE_TRANSFER_H_ */

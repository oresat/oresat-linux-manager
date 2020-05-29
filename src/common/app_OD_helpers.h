/**
 * A interface to the CANopen obejct dictionary for all apps to use.
 *
 * @file        app_OD_helpers.c
 * @ingroup     app_OD_helpers
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef APP_OD_HELPERS_H
#define APP_OD_HELPERS_H


#include "CANopen.h"
#include <syslog.h>
#include <stdint.h>


/**
 * @defgroup     App_Helpers CANdaemon App Helpers
 *
 * Useful helper functions for making apps.
 */


/**
 * @ingroup     App_Helpers
 * @{
 */



/**
 * Return values for app_OD_read() and app_OD_write().
 * For long explination see app_OD_error_str.
 */
typedef enum {
    /** No error */
    APP_OD_NONE,
    /** Data is NULL. Most likely a DOMAIN type entry */
    APP_OD_NULL_DATA,
    /** Index does not exist */
    APP_OD_INDEX,
    /** Sub index does not exist */
    APP_OD_SUBINDEX,
    /** Can't write a readonly entry */
    APP_OD_READONLY,
    /** Can't read a writeonly entry */
    APP_OD_WRITEONLY,
    /** Data is a DOMAIN type */
    APP_OD_DOMAIN,
    /** OD data size does not match input data type size */
    APP_OD_LENGTH,
} APP_OD_ERROR_ENUM;


/**
 * A nice wrapper for apps to not worry about CO->SDO[].
 *
 * @param index Index of object in the Object dictionary.
 * @param pODFunc Pointer to @ref CO_SDO_OD_function, specified by application.
 * If NULL, @ref CO_SDO_OD_function will not be used on this object.
 * @param object Pointer to object, which will be passed to @ref CO_SDO_OD_function.
 * @param flags Pointer to array of #CO_SDO_OD_flags_t defined externally. If
 * zero, #CO_SDO_OD_flags_t will not be used on this OD entry.
 * @param flagsSize Size of the above array. It must be equal to number
 * of sub-objects in object dictionary entry. Otherwise #CO_SDO_OD_flags_t will
 * not be used on this OD entry.
 */
void app_OD_configure(
        uint16_t index,
        CO_SDO_abortCode_t (*pODFunc)(CO_ODF_arg_t *ODF_arg),
        void *object,
        uint8_t *flags,
        uint8_t flagsSize);


/**
 * Find the location in the OD array from the OD index value.
 * Mostly a copy from CO_SDO.* that is for apps and not CANopenNode.
 *
 * @param index OD index for OD entry
 *
 * @return array location or 0xFFFF for failure.
 */
uint16_t app_OD_find(uint16_t index);


/**
 * Reads data into object dictionary.
 * Mostly a copy from CO_SDO.* that is for apps and not CANopenNode.
 *
 * @param index OD index for OD entry
 * @param subIndex OD sub-index for OD entry
 * @param data Buffer for copy data from OD
 * @param length Length of data buffer in bytes
 *
 * @return app_OD_error value.
 */
APP_OD_ERROR_ENUM app_OD_read(
        uint16_t index,
        uint16_t subIndex,
        void *data,
        uint16_t *length);


/**
 * Writes data into object dictionary.
 * Mostly a copy from CO_SDO.* that is for apps and not CANopenNode.
 *
 * @param index OD index for OD entry
 * @param subIndex OD sub-index for OD entry
 * @param data Data buffer to copy into OD
 * @param length Length of data buffer in bytes
 *
 * @return app_OD_error value.
 */
APP_OD_ERROR_ENUM app_OD_write(
        uint16_t index,
        uint16_t subIndex,
        void *data,
        uint16_t length);


/** @} */
#endif

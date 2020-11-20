/**
 * Helper fuctions for the object dictionary.
 *
 * @file        OD_helpers.h
 * @ingroup     OD_helpers
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef OD_HELPERS_H
#define OD_HELPERS_H


#include "CANopen.h"
#include <stdint.h>

/**
 * @defgroup    OD_helpers Object Dictionary Helpers
 * @{
 *
 * Nice wrapper functions to interface to the Object Dictionary.
 */

/**
 * Find the location in the OD array from the OD index value.
 *
 * Mostly a copy from CO_SDO.* that is for OLM and not for SDO.
 *
 * @param index OD index for OD entry
 *
 * @return array location or 0xFFFF for failure.
 */
uint16_t OD_find(uint16_t index);


/**
 * Used to read data from the object dictionary.
 *
 * Mostly a copy from CO_SDO.* that is for OLM and not for SDO.
 *
 * @param index OD index for OD entry
 * @param subIndex OD sub-index for OD entry
 * @param data Buffer for copy data from OD
 * @param length Length of data buffer in bytes
 *
 * @return 0 or CO_SDO_abortCode_t value on error.
 */
int OD_read(
        uint16_t index,
        uint16_t subIndex,
        void *data,
        uint16_t length);


/**
 * Used to write data into the object dictionary.
 *
 * Mostly a copy from CO_SDO.* that is for OLM and not for SDO.
 *
 * @param index OD index for OD entry
 * @param subIndex OD sub-index for OD entry
 * @param data Data buffer to copy into OD
 * @param length Length of data buffer in bytes
 *
 * @return 0 or CO_SDO_abortCode_t value on error.
 */
int OD_write(
        uint16_t index,
        uint16_t subIndex,
        void *data,
        uint16_t length);


/**
 * Used to get the legth of an entry in the object dictionary.
 *
 * @param index OD index for OD entry
 * @param subIndex OD sub-index for OD entry
 *
 * @return length of the entry or negative CO_SDO_abortCode_t on error.
 */
int OD_get_length(uint16_t index, uint16_t sub_index);


/** @} */
/****************************************************************************/


/**
 * @ingroup     App_Helpers
 * @{
 */


/**
 * Allows app to register Object Dictionary Functions (ODF).
 *
 * A nice wrapper ontop of CO_OD_configure() for apps to not worry
 * about CO->SDO[] when registering ODFs.
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
 * Allow apps to reads data from the object dictionary.
 *
 * One-to-one wrapper for OD_read() that follows app_* standard.
 *
 * @param index OD index for OD entry
 * @param subIndex OD sub-index for OD entry
 * @param data Buffer for copy data from OD
 * @param length Length of data buffer in bytes
 *
 * @return 0 or CO_SDO_abortCode_t value on error.
 */
int app_OD_read(
        uint16_t index,
        uint16_t subIndex,
        void *data,
        uint16_t length);


/**
 * Allow apps to write data into the object dictionary.
 *
 * One-to-one wrapper for OD_write() that follows app_* standard.
 *
 * @param index OD index for OD entry
 * @param subIndex OD sub-index for OD entry
 * @param data Data buffer to copy into OD
 * @param length Length of data buffer in bytes
 *
 * @return 0 or CO_SDO_abortCode_t value on error.
 */
int app_OD_write(
        uint16_t index,
        uint16_t subIndex,
        void *data,
        uint16_t length);


/**
 * Allow apps to get the length of an entry's data in the object dictionary.
 *
 * One-to-one wrapper for OD_get_length() that follows app_* standard.
 *
 * @param index OD index for OD entry
 * @param subIndex OD sub-index for OD entry
 *
 * @return length of the entry or negative CO_SDO_abortCode_t on error.
 */
int app_OD_get_length(uint16_t index, uint16_t sub_index);


/** @} */
#endif

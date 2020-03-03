#ifndef APP_OD_HELPERS_H
#define APP_OD_HELPERS_H


#include "CANopen.h"
#include <syslog.h>
#include <stdint.h>


/**
 * Return values for app_OD_read() and app_OD_write().
 * For long explination see app_OD_error_str.
 */
enum APP_OD_ERROR_ENUM {
    APP_OD_NONE,
    APP_OD_INDEX,
    APP_OD_SUBINDEX,
    APP_OD_READONLY,
    APP_OD_WRITEONLY,
    APP_OD_DOMAIN,
    APP_OD_LENGTH,
};


/**
 * A nice wrapper for apps to not worry about CO->SDO[].
 */
void app_OD_configure(
        uint16_t index,
        CO_SDO_abortCode_t (*pODFunc)(CO_ODF_arg_t *ODF_arg),
        void *object,
        uint8_t *flags,
        uint8_t flagsSize);


/**
 * A nice function to log message in syslogs with a standard format.
 *
 * @param app_name: for application name
 * @param priority: for log proprity
 * @param message: the message to log
 */
void app_log_message(const char *app_name, int priority, const char *message);


/**
 * Find the location in the OD array from the OD index value.
 * Mostly a copy from CO_SDO.* that is for apps and not CANopenNode.
 *
 * @param index: OD index for OD entry
 *
 * @return array location or 0xFFFF for failure.
 */
uint16_t app_OD_find(uint16_t index);


/**
 * Reads data into object dictionary.
 * Mostly a copy from CO_SDO.* that is for apps and not CANopenNode.
 *
 * @param index: OD index for OD entry
 * @param subIndex: OD sub-index for OD entry
 * @param data Buffer: for copy data from OD
 * @param length: Length of data buffer in bytes
 *
 * @return app_OD_error value.
 */
int app_OD_read(
        uint16_t index,
        uint16_t subIndex,
        void *data,
        uint16_t *length);


/**
 * Writes data into object dictionary.
 * Mostly a copy from CO_SDO.* that is for apps and not CANopenNode.
 *
 * @param index: OD index for OD entry
 * @param subIndex: OD sub-index for OD entry
 * @param data: Data buffer to copy into OD
 * @param length: Length of data buffer in bytes
 *
 * @return app_OD_error value.
 */
int app_OD_write(
        uint16_t index,
        uint16_t subIndex,
        void *data,
        uint16_t length);


#endif

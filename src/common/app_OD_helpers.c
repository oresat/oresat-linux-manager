#include "CANopen.h"
#include "log_message.h"
#include "app_OD_helpers.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>


extern CO_OD_entry_t CO_OD[CO_OD_NoOfElements];


/**
 * For logging/printing app_OD_error as a string.
 * Also long explination for app_OD_error enum.
 */
const char *APP_OD_ERROR_STRING[] = {
    "No error",
    "Input data was null",
    "OD index not found",
    "OD subindex not found",
    "Attempted to write a read-only object",
    "Attempted to read a write-only object",
    "Attempted to access a domain type",
    "Attempted to write an object that wont fit in OD entry", // can't write a int64 into int8
};


const char*
get_error_string(APP_OD_ERROR_ENUM error) {
    if( error >= 0)
        return APP_OD_ERROR_STRING[-error];
    return "";
}


void
app_OD_configure(
        uint16_t index,
        CO_SDO_abortCode_t (*pODFunc)(CO_ODF_arg_t *ODF_arg),
        void *object,
        uint8_t *flags,
        uint8_t flagsSize) {

    CO_OD_configure(CO->SDO[0], index, pODFunc, object, flags, flagsSize);
}


void
app_log_message(const char *app_name, int priority, const char *message) {
    char *format = "";

    // merge strings
    strncat(format, app_name, strlen(format));
    strncat(format, ": ", strlen(format));
    strncat(format, message, strlen(format));

    log_message(priority, format);
}


uint16_t
app_OD_find(uint16_t index){
    uint16_t cur, min, max;
    const CO_OD_entry_t* object;

    // Fast search algorithm
    min = 0U;
    max = CO_OD_NoOfElements - 1U;
    while(min < max){
        cur = (min + max) / 2;
        object = &CO_OD[cur];
        // Is object matched
        if(index == object->index){
            return cur;
        }
        if(index < object->index){
            max = cur;
            if(max) max--;
        }
        else
            min = cur + 1U;
    }

    if(min == max){
        object = &CO_OD[min];
        // Is object matched
        if(index == object->index){
            return min;
        }
    }

    return 0xFFFFU;  /* object does not exist in OD */
}


APP_OD_ERROR_ENUM
app_OD_read(uint16_t index, uint16_t sub_index, void *data, uint16_t *length) {
    CO_OD_entry_t* object = NULL;
    int8_t *OD_data = NULL;
    uint16_t OD_entry_num;
    uint16_t OD_length;
    uint16_t OD_attribute;

    if(data == NULL)
        return APP_OD_NULL_DATA; // No data pointer for return

    // Get object location
    OD_entry_num = app_OD_find(index);
    if(OD_entry_num == 0xFFFE)
        return APP_OD_INDEX; // Index not found

    // Get object
    object = &CO_OD[OD_entry_num];

    // Check if sub index is valid
    if(sub_index >= object->maxSubIndex)
        return APP_OD_SUBINDEX; // Sub index does not exist

    // Figure out OD entry type
    if(object->maxSubIndex == 0U) { // Object type is Variable
        OD_attribute = object->attribute;
        OD_length = object->length;
        OD_data = object->pData;
    }
    else if(object->attribute != 0U) { // Object type is Array
        OD_attribute = object->attribute;
        if(sub_index == 0) {
            // First sub_index is readonly, it holds the length of Array
            OD_attribute &= ~(CO_ODA_WRITEABLE | CO_ODA_RPDO_MAPABLE);
            OD_attribute |= CO_ODA_READABLE;
            OD_length = sizeof(object->maxSubIndex);
            memcpy(&object->maxSubIndex, OD_data, sizeof(object->maxSubIndex));
        }
        else { // array data
            OD_length = object->length;
            OD_data = ((int8_t*)object->pData) + ((sub_index-1) * object->length);
        }
    }
    else { // Object type is Record
        OD_attribute = ((const CO_OD_entryRecord_t*)(object->pData))[sub_index].attribute;
        OD_length = ((const CO_OD_entryRecord_t*)(object->pData))[sub_index].length;
        OD_data = ((const CO_OD_entryRecord_t*)(object->pData))[sub_index].pData;
    }

    if((OD_attribute & CO_ODA_READABLE) == 0)
        return APP_OD_WRITEONLY;

    if(OD_data == NULL)
        return APP_OD_DOMAIN; // Is a domain type

    CO_LOCK_OD();

    // Copy data
    *length = OD_length;
    memcpy(data, OD_data, OD_length);

    CO_UNLOCK_OD();

    return APP_OD_NONE;
}


APP_OD_ERROR_ENUM
app_OD_write(uint16_t index, uint16_t sub_index, void *data, uint16_t length) {
    CO_OD_entry_t* object = NULL;
    int8_t *OD_data = NULL;
    uint16_t OD_entry_num;
    uint16_t OD_length;
    uint16_t OD_attribute;

    if(data == NULL || length == 0)
        return APP_OD_NULL_DATA; // No data to write

    OD_entry_num = app_OD_find(index);
    if(OD_entry_num == 0xFFFE)
        return APP_OD_INDEX; // Index not found

    // Get object
    object = &CO_OD[OD_entry_num];

    if(sub_index >= object->maxSubIndex)
        return APP_OD_SUBINDEX; // Sub index does not exist

    // Figure out OD entry type
    if(object->maxSubIndex == 0U) { //Object type is Varaible
        OD_attribute = object->attribute;
        OD_length = object->length;
        OD_data = object->pData;
    }
    else if(object->attribute != 0U) { // Object type is Array
        OD_attribute = object->attribute;
        if(sub_index == 0) {
            // First sub_index is readonly, it holds the length of Array
            OD_attribute &= ~(CO_ODA_WRITEABLE | CO_ODA_RPDO_MAPABLE);
            OD_attribute |= CO_ODA_READABLE;
            OD_length = sizeof(object->maxSubIndex);
            memcpy(OD_data, &object->maxSubIndex, sizeof(object->maxSubIndex));
        }
        else { // Array data
            OD_length = object->length;
            OD_data = ((int8_t*)object->pData) + ((sub_index-1) * object->length);
        }
    }
    else { // Object type is Record
        CO_OD_entryRecord_t *temp = (CO_OD_entryRecord_t *)object->pData;
        OD_attribute = temp[sub_index].attribute;
        OD_length = temp[sub_index].length;
        OD_data = temp[sub_index].pData;
    }

    if((OD_attribute & CO_ODA_WRITEABLE) == 0)
        return APP_OD_READONLY; // Attempted to write a read-only object

    if(OD_data == NULL)
        return APP_OD_DOMAIN; // Is a domain type, can't write it

    if(length > OD_length)
        return APP_OD_LENGTH; // Length of service parameter does not match

    CO_LOCK_OD();

    // copy the data
    OD_length = length;
    memcpy(OD_data, data, length);

    CO_UNLOCK_OD();

    return true;
}


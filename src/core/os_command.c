/**
 * OS Command (bash commands over CANbus) ODF
 *
 * @file        os_command.c
 * @ingroup     os_command
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "os_command.h"
#include "CANopen.h"
#include "logging.h"
#include "utility.h"
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SDO_BLOCK_LEN  (127 * 7)
#define BUFFER_LEN     1024
#define BUFFER_LEN_MAX (BUFFER_LEN * 128)

/** OS command status values defined by CiA 301 */
enum os_command_status {
    os_cmd_no_error_no_reply = 0x00,
    os_cmd_no_error_reply = 0x01,
    os_cmd_error_no_reply = 0x02,
    os_cmd_error_reply = 0x03,
    // 0x04 to 0xFE reserved
    os_cmd_executing = 0xFF,
};

void
co_command_async(os_command_t *data) {
    FILE *pipe;
    char *temp;
    int c;

    if (data == NULL) {
        log_printf(LOG_DEBUG, "os command is missing argument data");
        return;
    } else if (OD_OSCommand.status != os_cmd_executing) {
        return; // nothing todo
    }

    if (data->command == NULL) {
        CO_LOCK_OD();
        OD_OSCommand.status = os_cmd_error_no_reply;
        CO_UNLOCK_OD();
        log_printf(LOG_DEBUG, "no command in excuting state");
        return;
    }

    if (data->command_len < 50)
        log_printf(LOG_DEBUG, "running bash command: %s", data->command);
    else
        log_printf(LOG_DEBUG, "running long bash command");

    pipe = popen(data->command, "r");
    if (pipe == NULL) {
        CO_LOCK_OD();
        OD_OSCommand.status = os_cmd_error_no_reply;
        CO_UNLOCK_OD();
        log_printf(LOG_ERR, "popen failed");
    } else {
        // initialize buffer
        FREE(data->reply_buf);
        data->reply_buf_len = BUFFER_LEN;
        if ((data->reply_buf = malloc(BUFFER_LEN)) == NULL) {
            CO_LOCK_OD();
            OD_OSCommand.status = os_cmd_no_error_no_reply;
            CO_UNLOCK_OD();
            log_printf(LOG_ERR, "bash reply malloc failed");
            return;
        }

        for (data->reply_len = 0; (c = fgetc(pipe)) != EOF; ++data->reply_len) {
            if (data->reply_len > data->reply_buf_len) { // grow buffer
                if (data->reply_len > BUFFER_LEN_MAX) {
                    log_printf(LOG_INFO, "bash reply max limit hit");
                    break; // max len reached
                }

                data->reply_buf_len *= 2;

                if ((temp = realloc(data->reply_buf, data->reply_buf_len))
                    == NULL) {
                    log_printf(LOG_ERR, "bash reply realloc failed");
                    break; // realloc failed;
                } else {
                    log_printf(LOG_DEBUG, "bash reply realloc to %d",
                               data->reply_buf_len);
                    data->reply_buf = temp;
                }
            }
            data->reply_buf[data->reply_len] = (char)c; // old compiler fix
        }

        CO_LOCK_OD();
        if (data->reply_len == 0)
            OD_OSCommand.status = os_cmd_no_error_no_reply;
        else
            OD_OSCommand.status = os_cmd_no_error_reply;
        CO_UNLOCK_OD();
    }

    return;
}

CO_SDO_abortCode_t
OS_COMMAND_1023_ODF(CO_ODF_arg_t *ODF_arg) {
    os_command_t *data = (os_command_t *)ODF_arg->object;
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    uint32_t bytes_left;

    if (data == NULL)
        return CO_SDO_AB_DATA_LOC_CTRL;

    switch (ODF_arg->subIndex) {
    case OD_1023_1_OSCommand_command: // bash command, domain, readwrite

        if (ODF_arg->reading) {
            if (ODF_arg->firstSegment == true) {
                if (data->command == NULL)
                    return CO_SDO_AB_NO_DATA;

                ODF_arg->offset = 0;
                ODF_arg->dataLengthTotal = strlen(data->command) + 1;
            }

            // Check if there are more segements needed
            bytes_left = ODF_arg->dataLengthTotal - ODF_arg->offset;
            if (bytes_left > SDO_BLOCK_LEN) { // more segements needed
                ODF_arg->dataLength = SDO_BLOCK_LEN;
                ODF_arg->lastSegment = false;
            } else { // last segement
                ODF_arg->dataLength = bytes_left;
                ODF_arg->lastSegment = true;
            }

            memcpy(ODF_arg->data, &data->command[ODF_arg->offset],
                   ODF_arg->dataLength);
        } else { // writing
            uint32_t len;

            // add on incase it is missing '\0'
            if (ODF_arg->dataLengthTotal > BUFFER_LEN_MAX)
                return CO_SDO_AB_GENERAL;
            else if (ODF_arg->dataLengthTotal != 0)
                len = ODF_arg->dataLengthTotal + 1;
            else
                len = ODF_arg->dataLength + 1;

            if (ODF_arg->firstSegment) {
                FREE(data->command);
                data->command_len = len;
                ODF_arg->offset = 0;

                // free reply buffer
                FREE(data->reply_buf);
                data->reply_buf_len = 0;
                data->reply_buf = 0;

                if ((data->command = malloc(data->command_len)) == NULL)
                    return CO_SDO_AB_OUT_OF_MEM;
            }

            memcpy(&data->command[ODF_arg->offset], ODF_arg->data,
                   ODF_arg->dataLength);

            if (ODF_arg->lastSegment) {
                data->command[len - 1] = '\0';
                OD_OSCommand.status = os_cmd_executing;
            }
        }

        break;

    case OD_1023_3_OSCommand_reply: // bash command reply, domain, readonly
        if (ODF_arg->reading) {
            if (ODF_arg->firstSegment) {
                if (OD_OSCommand.status != os_cmd_no_error_reply
                    && OD_OSCommand.status != os_cmd_error_reply)
                    return CO_SDO_AB_NO_DATA;

                ODF_arg->offset = 0;
                ODF_arg->dataLengthTotal = data->reply_len;
            }

            // Check if there are more segements needed
            bytes_left = ODF_arg->dataLengthTotal - ODF_arg->offset;
            if (bytes_left > SDO_BLOCK_LEN) { // more segements needed
                ODF_arg->dataLength = SDO_BLOCK_LEN;
                ODF_arg->lastSegment = false;
            } else { // last segement
                ODF_arg->dataLength = bytes_left;
                ODF_arg->lastSegment = true;
            }

            memcpy(ODF_arg->data, &data->reply_buf[ODF_arg->offset],
                   ODF_arg->dataLength);
        } else {
            return CO_SDO_AB_READONLY;
        }

        break;
    }

    return ret;
}

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

#ifndef OS_COMMAND_H
#define OS_COMMAND_H

#include "CANopen.h"
#include <stdint.h>
#include <stdio.h>

typedef struct {
    /** Bash command buffer. */
    char *command;
    /** Lenght of the Bash command buffer. */
    int command_len;
    /** Reply buffer. */
    char *reply_buf;
    /** Reply buffer length. */
    uint32_t reply_buf_len;
    /** Reply length in the buffer. */
    uint32_t reply_len;
} os_command_t;

/**
 * Create an os_command_t object
 *
 * @see os_command_destroy
 */
os_command_t *os_command_create();

/**
 * Destroy an os_command_t object
 *
 * @param data os_command_t object to destroy
 *
 * @see os_command_create
 */
void os_command_destroy(os_command_t *data);

/**
 * Run the OS command received over the CAN bus.
 *
 * @param data os command data
 */
void os_command_async(os_command_t *data);

CO_SDO_abortCode_t os_command_odf(CO_ODF_arg_t *ODF_arg);

#endif /* OS_COMMAND_H */

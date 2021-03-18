/**
 * Standard log message functions for OLM's internals to use.
 *
 * @file        log_message.c
 * @ingroup     log_message
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "log_message.h"
#include <string.h>
#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

void
log_message(int priority, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vsyslog(priority, fmt, args);
    va_end(args);

    /*
    va_start(args, fmt);
    vfprintf((priority > LOG_WARNING ? stdout : stderr), fmt, args);
    if(fmt[strlen(fmt)] != '\n')
        vfprintf("\n");
    va_end(args);
    */
}

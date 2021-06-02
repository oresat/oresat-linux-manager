/**
 * Standard log message functions for OLM's internals to use.
 *
 * @file        logging.c
 * @ingroup     logging
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "logging.h"
#include <stdarg.h>
#include <stdio.h>
#include <syslog.h>

void
log_printf(int priority, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vsyslog(priority, fmt, args);
    va_end(args);
}

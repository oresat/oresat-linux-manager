#include "log_message.h"
#include <string.h>
#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>


void
log_message(int priority, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vsyslog(priority, fmt, args);
	vfprintf((priority > LOG_WARNING ? stdout : stderr), fmt, args);
	va_end(args);
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


void log_error_ODF(char *ODF_name, CO_ODF_arg_t *ODF_arg, char *message) {
    if(ODF_arg->reading)
        log_message(
                LOG_ERR,
                "%s index %d subindex %d read: %s",
                ODF_name,
                ODF_arg->index,
                ODF_arg->subIndex,
                message);
    else
        log_message(
                LOG_ERR,
                "%s index %d subindex %d write: %s",
                ODF_name,
                ODF_arg->index,
                ODF_arg->subIndex,
                message);
}


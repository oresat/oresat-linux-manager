/**
 * Standard log message functions for OLM's internals to use.
 *
 * @file        logging.h
 * @ingroup     logging
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef LOG_PRINTF_H
#define LOG_PRINTF_H

#include <syslog.h>
#include <systemd/sd-bus.h>

/**
 * Logs the message in syslog and will output to stderr/stdout, if available.
 * see man vsyslog for prioprity levels
 */
void
log_printf(int priority, const char *fmt, ...);

#define LOG_DBUS_GET_PROPERTY_ERROR(log_lvl, app_name, prop_name, err_name)    \
    log_printf(log_lvl, "app %s: dbus get property %s failed: %s", app_name,   \
               prop_name, err_name)

#define LOG_DBUS_SET_PROPERTY_ERROR(log_lvl, app_name, prop_name, err_name)    \
    log_printf(log_lvl, "app %s: dbus set property %s failed: %s", app_name,   \
               prop_name, err_name)

#define LOG_DBUS_PROPERTY_READ_ERROR(log_lvl, app_name, prop_name, err_name)   \
    log_printf(log_lvl, "app %s: dbus property %s read failed: %s", app_name,  \
               prop_name, err_name)

#define LOG_DBUS_CALL_METHOD_ERROR(log_lvl, app_name, signal_name, err_name)   \
    log_printf(log_lvl, "app %s: dbus method %s call failed: %s", app_name,    \
               signal_name, err_name)

#define LOG_DBUS_METHOD_READ_ERROR(log_lvl, app_name, signal_name, err_name)   \
    log_printf(log_lvl, "app %s: dbus method %s read failed: %s", app_name,    \
               signal_name, err_name)

#endif /* LOG_PRINTF_H */

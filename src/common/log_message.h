/**
 * Standard log message functions for OLM's internals to use.
 *
 * @file        log_message.h
 * @ingroup     log_message
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <syslog.h>

/*
 * Logs the message in syslog and will output to stderr/stdout, if available.
 * see man vsyslog for prioprity levels
 */
void log_message(int priority, const char *fmt, ...);

#define LOG_DBUS_PROPERTY_READ_ERROR(log_lvl, app_name, prop_name) \
    log_message(log_lvl, "app %s: dbus property %s read failed", app_name, prop_name)

#define LOG_DBUS_SIGNAL_READ_ERROR(log_lvl, app_name, signal_name) \
    log_message(log_lvl, "app %s: dbus signal %s read failed", app_name, signal_name)

#define LOG_DBUS_SIGNAL_USERDATA_ERROR(log_lvl, app_name, signal_name) \
    log_message(log_lvl, "app %s: dbus signal %s is missing userdata", app_name, signal_name)

#define LOG_DBUS_SIGNAL_MATCH_ERROR(log_lvl, app_name, signal_name) \
    log_message(log_lvl, "app %s: dbus signal %s match failed", app_name, signal_name)

#define LOG_DBUS_METHOD_READ_ERROR(log_lvl, app_name, signal_name) \
    log_message(log_lvl, "app %s: dbus method %s read failed", app_name, signal_name)

#define LOG_DBUS_CALL_METHOD_ERROR(log_lvl, app_name, signal_name) \
    log_message(log_lvl, "app %s: dbus method %s call failed", app_name, signal_name)

#endif /* LOG_MESSAGE_H */

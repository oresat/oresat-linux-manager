/**
 * A convenience header to include all dependencies for an app.
 *
 * @file        app_include.h
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef APP_INCLUDE_H
#define APP_INCLUDE_H


#include "CANopen.h"
#include "daemon_manager.h"
#include "dbus_controller.h"
#include "CO_fread.h"
#include "CO_fwrite.h"
#include "log_message.h"
#include "OD_helpers.h"


/**
 * Gobal for all apps to use to get acces to OLM's dbus connetion.
 * Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;


#endif

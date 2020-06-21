/**
 * A convenience header to include all dependencies for an app.
 *
 * @file        app_include.h
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https//github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef APP_INCLUDE_H
#define APP_INCLUDE_H


#include "CANopen.h"
#include "daemon_controller.h"
#include "dbus_controller.h"
#include "file_transfer.h"
#include "log_message.h"
#include "OD_helpers.h"


/**
 * Gobal for all apps to use to get acces to the CANdaemon dbus connetion.
 * Apps should treat this as readonly.
 */
extern dbus_data_t APP_DBUS;


#endif

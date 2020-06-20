/**
 * App helpers.
 *
 * @file        app_helpers.h
 * @ingroup     app_helpers
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef APP_HELPERS_H
#define APP_HELPERS_H


/**
 * @ingroup app_helpers
 * @{
 */


#include "log_message.h"
#include "app_dbus_controller.h"
#include "app_OD_helpers.h"
#include "daemon_controller.h"
#include "file_transfer.h"


/** The dbus destination for all oresat programs */
#define CANDAEMON_DESTINATION     "org.OreSat.CANdaemon"
/** The dbus object path for all oresat programs */
#define CANDAEMON_OBJECT_PATH     "/org/OreSat/CANdaemon"


/**
 * Gobal for all apps to use.
 * Outside of app_dbus_controller.c it should be treated as readonly.
 */
app_dbus_data_t APPS_DBUS;


/** @} */
#endif

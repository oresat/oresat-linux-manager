/**
 * App for accesing the object dictionary from other processes. Only for testing/debugging.
 *
 * @file        OD_app.h
 * @ingroup     OD_app
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef OD_APP_H
#define OD_APP_H


#include "CANopen.h"
#include <systemd/sd-bus.h>
#include <pthread.h>


/**
 * @ingroup     test_apps
 * @defgroup    OD_app Object Dictionary app
 * @{
 *
 * An dbus server app that allow other programs to read/write to the Object Dictionary. Used for testing.
 */


/**
 * @brief Main function for the object dictionary app that will run the dbus server.
 */
void OD_app_thread();


/**
 * @brief Sets up the OD app and the extra thread for OD_app_thread().
 */
int setup_OD_app();


/** @} */
#endif

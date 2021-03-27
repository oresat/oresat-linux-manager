/**
 * OreSat Linux updater dameon app.
 *
 * @file        updater_odf.h
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef UPDATER_ODF_H
#define UPDATER_ODF_H

#include "CANopen.h"

CO_SDO_abortCode_t updater_ODF(CO_ODF_arg_t *ODF_arg);

#endif

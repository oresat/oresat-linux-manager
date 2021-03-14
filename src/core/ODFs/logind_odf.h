/**
 * ODF for interfacing with systemd power setting.
 *
 * @file        logind_odf.h
 * @ingroup     core_odfs
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef LOGIND_ODF_H
#define LOGIND_ODF_H

#include "CANopen.h"

/**
 * Give the CAN network manager control over board's power settings
 * (issue poweroff and reboot commands).
 */
CO_SDO_abortCode_t logind_ODF(CO_ODF_arg_t *ODF_arg);

#endif /* LOGIND_ODF_H */

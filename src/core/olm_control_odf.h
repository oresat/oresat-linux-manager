/**
 * OLM control ODF for reboot and poweroff commands.
 *
 * @file        olm_control_odf.h
 * @ingroup     olm_control_odf
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef OLM_CONTROL_ODF_H
#define OLM_CONTROL_ODF_H

#include "CANopen.h"

CO_SDO_abortCode_t olm_control_ODF(CO_ODF_arg_t *ODF_arg);

#endif /* OLM_CONTROL_ODF_H */

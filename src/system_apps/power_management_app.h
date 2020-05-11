#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H


#include "CANopen.h"


/**
 * Give the candaemon / CAN network manager control over board's power settings
 * (issue poweroff and reboot).
 */
CO_SDO_abortCode_t power_management_ODF(CO_ODF_arg_t *ODF_arg);


#endif

/**
 * System information ODF.
 *
 * @file        system_info.h
 * @ingroup     system_info
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux systems.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H


#include "CANopen.h"


/**
 * Configure the OD function for system info.
 *
 * @return 0 on success
 */
int system_info_setup(void);


/**
 * Configure the OD function for system info.
 *
 * @return 0 on success or negative errno on error
 */
int system_info_end(void);


/**
 * Callback for using inside CO_OD_configure() function for getting the systems
 * info.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t system_info_ODF(CO_ODF_arg_t *ODF_arg);


#endif /* SYSTEM_INFO_H */

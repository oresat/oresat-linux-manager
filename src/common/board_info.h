/**
 * Board Info Object Dictionary Function.
 *
 * @file        board_info.h
 * @ingroup     board_info
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef BOARD_INFO_H
#define BOARD_INFO_H


#include "CANopen.h"
#include "CO_driver.h"


/**
 * Configure the OD function for board info.
 *
 * @return 0 on success
 */
int board_info_setup(void);


/**
 * Configure the OD function for board info.
 *
 * @return 0 on success or negative errno on error
 */
int board_info_end(void);


/**
 * Callback for using inside CO_OD_configure() function for getting the boards
 * info.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t board_info_ODF(CO_ODF_arg_t *ODF_arg);


#endif

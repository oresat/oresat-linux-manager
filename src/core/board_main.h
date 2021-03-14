/**
 * OreSat board main header.
 *
 * @file        board_main.h
 * @ingroup     board_main
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef BOARD_MAIN_H
#define BOARD_MAIN_H

#include "olm_app.h"

olm_app_t **board_main(void);

#endif /* BOARD_MAIN_H */

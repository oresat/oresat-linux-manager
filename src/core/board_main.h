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

extern olm_app_t **APPS;

/** @brief Configure all the board ODFs (Object Dictionary Functions). */
void
board_init(void);

#endif /* BOARD_MAIN_H */

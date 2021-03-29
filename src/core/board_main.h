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

typedef struct {
    olm_app_t* apps;
    unsigned int apps_len;
} olm_board_t;

#define OLM_BOARD_MALLOC_DEFAULT(out) \
    if ((out = malloc(sizeof(olm_board_t))) != NULL) { \
        out->apps = NULL; \
        out->apps_len = 0; \
    }

/**
 * @brief Configure OLM for a board. Used to fill out a @ref olm_board_t and
 * add board ODFs.
 *
 * @param A pointer to a @ref olm_board_t object
 *
 * @return 1 on success or negative errno value on failure
 */
int board_init(olm_board_t *board);

/** @brief Configure OLM for a specific board. */
void board_loop(void);

#endif /* BOARD_MAIN_H */

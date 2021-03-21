/**
 * Async loop for OLM core.
 *
 * @file        async_loop.c
 * @ingroup     async_loop
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for apps running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include <unistd.h>

#define ASYNC_DELAY     100000

void
async_loop(void) {
    usleep(ASYNC_DELAY);
}

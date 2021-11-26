/**
 * Module for interfacing with Logind over D-Bus.
 *
 * @file        logind.h
 * @ingroup     daemons
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef LOGIND_MODULE_H
#define LOGIND_MODULE_H

/** Call reboot thru logind. */
int logind_reboot(void);

/** Call poweroff thru logind. */
int logind_poweroff(void);

#endif /* LOGIND_MODULE_H */

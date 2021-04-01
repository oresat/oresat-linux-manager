/**
 * Module for interfacing with Logind over D-Bus.
 *
 * @file        logind.h
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef LOGIND_MODULE_H
#define LOGIND_MODULE_H

int logind_reboot(void);
int logind_poweroff(void);

#endif /* LOGIND_MODULE_H */

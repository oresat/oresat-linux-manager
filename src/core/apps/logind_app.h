/**
 * App for interfacing with systemd power setting.
 *
 * @file        logind_app.h
 * @ingroup     logind_app
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef LOGIND_APP_H
#define LOGIND_APP_H

int logind_reboot(void);
int logind_poweroff(void);

#endif /* LOGIND_APP_H */

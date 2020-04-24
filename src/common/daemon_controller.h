#ifndef DAEMON_CONTROLLER_H
#define DAEMON_CONTROLLER_H


#include "CANopen.h"
#include "CO_driver.h"




/**
 * Give the candaemon / network manager control over board powe (issue poweroff
 * and reboot).
 */
CO_SDO_abortCode_t systemd_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * If an app wants its daemon to be controlled by the candaemon the app must
 * calls this function in <app_name>_app_setup(). Daemons other than the
 * candameon and linux updater are not enable, so without call this function
 * in the apps setup function the daemon associate with the app will never be
 * started.
 *
 * @param: app_name is application name
 * @param: daemon_name is the daemon name
 *
 * @ return file descriptor for apps daemon
 */
int app_add_daemon(const char *app_name, const char *daemon_name);


#endif

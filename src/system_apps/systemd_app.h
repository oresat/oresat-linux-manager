#ifndef SYSTEMD_ODF_H
#define SYSTEMD_ODF_H


#include "CANopen.h"
#include "CO_driver.h"


typedef struct {
    char *service_name; // ie oresat-gps.service. If NULL there is no daeamon.
    int status; // current state of daemon
} DaemonData;


enum DaemonStates {
    running = 0,
    stopped = 1,
    failed = 2,
};


/**
 * Set up the systemd app  ODFs
 */
int systemd_app_setup(void);



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

int start_daemon(DaemonData *daemon);
int stop_daemon(DaemonData *daemon);

#endif

#ifndef UPDATER_H
#define UPDATER_H


#include "CANopen.h"
#include <systemd/sd-bus.h>
#include <pthread.h>


/**
 * Nice function for registering all dbus signal matches for the linux updater.
 */
int linux_updater_dbus_signal_match(void);


/**
 * ODF callbacks for getting the linux updater's ODF.
 */
CO_SDO_abortCode_t updater_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * DBus callbacks for read the emit when changes signal.
 */
int read_status_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);


#endif

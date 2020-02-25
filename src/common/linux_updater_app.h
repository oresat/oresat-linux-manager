#ifndef UPDATER_H
#define UPDATER_H


#include "CANopen.h"
#include "CO_driver.h"
#include <systemd/sd-bus.h>
#include <pthread.h>


#define FILE_NAME_SIZE  100


/**
 * This is a nice way to share data between the dbus callbacks and
 * the ODF callbacks, since thery can be in different threads.
 * Ment to be a static global as it is shared between threads.
 */
typedef struct {
    // Current state of the dbus interface.
    bool dbus_running;
    // holds the current stat of the updater.
    int32_t current_state;
    // The number archive files available.
    uint32_t updates_available;
    // If an updating, this holds the name of archive file.
    char current_file[FILE_NAME_SIZE];
    // mutex for access
    pthread_mutex_t mutex;
} shared_data;


/**
 * Function is called on program startup. Used to set up ODFs.
 */
int linux_updater_ODF_setup(void);


/**
 * Main for the Linux updater app.
 */
int linux_updater_dbus_main(void);


/**
 * ODF callbacks for getting the linux updater's ODF.
 */
CO_SDO_abortCode_t updater_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * DBus callbacks for read the emit when changes signal.
 */
int read_status_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);


#endif

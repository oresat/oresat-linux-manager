#include "application.h"
#include "app_OD_helpers.h"
#include "file_transfer_ODF.h"
#include <systemd/sd-bus.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define DESTINATION     "org.OreSat.GPS"
#define INTERFACE_NAME  "org.OreSat.GPS"
#define OBJECT_PATH     "/org/OreSat/GPS"
#define APP_NAME        "GPS"


// Static variables
static sd_bus           *bus = NULL;
static bool             running = true;


// Static functions headers
static int read_gps_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);


// ***************************************************************************
// app ODF and dbus functions


int main_process_ODF_setup(void) {
    return 0;
}


int main_process_dbus_main(void) {
    int r;

    /* Connect to the bus */
    r = sd_bus_open_system(&bus);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Failed to connect to systemd bus.\n");
        return r;
    }

    r = sd_bus_match_signal(
            bus,
            NULL,
            NULL,
            OBJECT_PATH,
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            read_gps_cb,
            NULL);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Failed to add new signal match.\n");
        return r;
    }

    while (running) {
        // Process requests
        r = sd_bus_process(bus, NULL);
        if ( r < 0)
            app_log_message(APP_NAME, LOG_DEBUG, "Failed to processA bus.\n");
        else if (r > 0) // we processed a request, try to process another one, right-away
            continue;

        // Wait for the next request to process
        if (sd_bus_wait(bus, 100000) < 0)
            app_log_message(APP_NAME, LOG_DEBUG, "Bus wait failed.\n");
    }

    sd_bus_unref(bus);
    return 0;
}


// ***************************************************************************
// app callback functions


static int read_gps_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    int r;
    int16_t posX = 0;
    int16_t posY = 0;
    int16_t posZ = 0;
    int16_t velX = 0;
    int16_t velY = 0;
    int16_t velZ = 0;
    int32_t state;

    r = sd_bus_message_read(m, "ddd", &posX, &posY, &posZ); //, &velX, &velY, &velZ, &accX, &accY, &accZ);
    if (r < 0)
        return -1;

    r = sd_bus_message_read(m, "ddd", &velX, &velY, &velZ); //, &velX, &velY, &velZ, &accX, &accY, &accZ);
    if (r < 0)
        return -1;

    r = sd_bus_message_read(m, "i", &state);
    if (r < 0)
        return -1;

    app_OD_write(0x3003, 1, &posX, sizeof(float));
    app_OD_write(0x3003, 2, &posY, sizeof(float));
    app_OD_write(0x3003, 3, &posZ, sizeof(float));
    app_OD_write(0x3003, 4, &velX, sizeof(float));
    app_OD_write(0x3003, 5, &velY, sizeof(float));
    app_OD_write(0x3003, 6, &velZ, sizeof(float));
    app_OD_write(0x3001, 1, &state, sizeof(state));

    return 0;
}



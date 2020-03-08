#include "log_message.h"
#include "app_OD_helpers.h"
#include "file_transfer_ODF.h"
#include "application.h"
#include <systemd/sd-bus.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


#define DESTINATION     "org.OreSat.StarTracker"
#define INTERFACE_NAME  "org.OreSat.StarTracker"
#define OBJECT_PATH     "/org/OreSat/StarTracker"
#define APP_NAME        "StarTracker"


// Static variables
static sd_bus           *bus = NULL;
static bool             running = true;


// Static functions headers
static int read_prop_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);


/*****************************************************************************/
// app ODF and dbus functions


int main_process_app_setup(void) {
    return 0;
}

int main_process_app_main(void) {

    // DBus variables
    int r;

    // Connect to the bus
    r = sd_bus_open_system(&bus);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Failed to connect to systemd bus.\n");
        return r;
    }

    // Set up signal callback
    r = sd_bus_match_signal(
            bus,
            NULL,
            NULL,
            OBJECT_PATH,
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            read_prop_cb,
            NULL);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Failed to add PropertiesChanged signal match.\n");
        return r;
    }

    // Process requests
    while (running) {
        r = sd_bus_process(bus, NULL);
        if (r < 0)
            app_log_message(APP_NAME, LOG_DEBUG, "Failed to process bus.\n");
        else if (r > 0) // we processed a request, try to process another one, right-away
            continue;

        // Wait for the next request to process
        if (sd_bus_wait(bus, (uint64_t) -1) < 0)
            app_log_message(APP_NAME, LOG_DEBUG, "Bus wait failed.\n");
    }

    // Cleanup
    sd_bus_unref(bus);
    return 0;

}


// ***************************************************************************
// star tracker callback function


static int read_prop_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {

    // Initialize holding variables
    double dec = 0.0, ra = 0.0, ori = 0.0, timestamp = 0.0;
    char *solve_path = NULL;

    // Get the coordinates + timestamp
    if (sd_bus_get_property(bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME, "coor", ret_error, &m, "(dddd)") < 0)
        return -1; // failed to get property
    if (sd_bus_message_read(m, "(dddd)", &dec, &ra, &ori, &timestamp) < 0)
        return -1; // failed to decode dbus property

    // Get the solution image's filepath
    if (sd_bus_get_property(bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME, "filepath", ret_error, &m, "s") < 0)
        return -1; // failed to get property
    if (sd_bus_message_read(m, "s", &solve_path) < 0)
        return -1; // failed to decode dbus property

    // Debug printing
    // fprintf(stderr, "Dec: %.3f, RA: %.3f, Ori: %.3f, Time: %.3f, Path: %s\n", dec, ra, ori, timestamp, solve_path);

    // Cast to floats
    float f_dec = (float) dec;
    float f_ra = (float) ra;
    float f_ori = (float) ori;
    float f_timestamp = (float) timestamp;

    // Update OD
    app_OD_write(0x3101, 1, &f_dec, sizeof(f_dec));
    app_OD_write(0x3101, 2, &f_ra, sizeof(f_ra));
    app_OD_write(0x3101, 3, &f_ori, sizeof(f_ori));
    app_OD_write(0x3101, 4, &f_timestamp, sizeof(f_timestamp));
    app_OD_write(0x3102, 0, solve_path, strlen(solve_path));

    // Free memory (taken care of by sd-bus)
    // if (solve_path != NULL) {
    //     free(solve_path);
    //     solve_path = NULL;
    // }

    return 0;

}

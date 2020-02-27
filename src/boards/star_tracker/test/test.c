#include <systemd/sd-bus.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#define DESTINATION     "org.OreSat.StarTracker"
#define INTERFACE_NAME  "org.OreSat.StarTracker"
#define OBJECT_PATH     "/org/OreSat/StarTracker"


// Static variables
static sd_bus           *bus = NULL;
static bool             end_program = false;


// Static functions headers
static int prop_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);


// ***************************************************************************
// other star tracker functions


static int prop_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {

    // Initialize holding variables
    double declination = 0.0, right_ascension = 0.0, orientation = 0.0, timestamp = 0.0;
    char *solve_path = NULL;

    // Get the coordinates + timestamp
    if (sd_bus_get_property(bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME, "coor", ret_error, &m, "(dddd)") < 0)
        return 1; // failed to get property
    if (sd_bus_message_read(m, "(dddd)", &declination, &right_ascension, &orientation, &timestamp) < 0)
        return 1; // failed to decode dbus property

    // Get the solution image's filepath
    if (sd_bus_get_property(bus, DESTINATION, OBJECT_PATH, INTERFACE_NAME, "filepath", ret_error, &m, "s") < 0)
        return 1; // failed to get property
    if (sd_bus_message_read(m, "s", solve_path) < 0)
        return 1; // failed to decode dbus property

    printf("%f %f %f %f\n", declination, right_ascension, orientation, timestamp);

    // Free memory
    if (solve_path != NULL) {
        free(solve_path);
        solve_path = NULL;
    }

    return 0;
}



int main() {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    void* userdata = NULL;
    int r;

    // Connect to the bus
    r = sd_bus_open_system(&bus);
    if (r < 0) {
        printf("Failed to connect to systemd bus.\n");
        return r;
    }

    r = sd_bus_match_signal(
            bus,
            NULL,
            NULL,
            OBJECT_PATH,
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            prop_cb,
            userdata);
    if (r < 0) {
        printf("Failed to add new signal match.\n");
        return r;
    }

    while (end_program == false) {
        // Process requests
        r = sd_bus_process(bus, NULL);
        if (r < 0)
            printf("Failed to process bus.\n");
        else if (r > 0) // we processed a request, try to process another one, right-away
            continue;

        // Wait for the next request to process
        if (sd_bus_wait(bus, 100000) < 0)
            printf("Bus wait failed.\n");
    }

    sd_bus_error_free(&err);
    sd_bus_unref(bus);
    return 0;
}

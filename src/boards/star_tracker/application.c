#include "application.h"
#include "OD_helpers.h"
#include "file_transfer_ODF.h"
#include "log_message.h"
#include <systemd/sd-bus.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define DESTINATION     "org.OreSat.StarTracker"
#define INTERFACE_NAME  "org.OreSat.StarTracker"
#define OBJECT_PATH     "/org/OreSat/StarTracker"


// Static variables
static sd_bus           *bus = NULL;
static pthread_t        app_signal_thread_id;
static bool             end_program = false;


// Static functions headers
static int prop_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);
static void* app_signal_thread(void* arg);


int app_dbus_setup(void) {
    int r;
    void* userdata = NULL;

    // Connect to the bus
    r = sd_bus_open_system(&bus);
    if (r < 0) {
        log_message(LOG_ERR, "Failed to connect to systemd bus.\n");
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
        log_message(LOG_ERR, "Failed to add new signal match.\n");
        return r;
    }

    //start dbus signal thread
    if (pthread_create(&app_signal_thread_id, NULL, app_signal_thread, NULL) != 0) {
        log_message(LOG_ERR, "Failed to start dbus signal thread.\n");
        return -1;
    }

    return 0;
}


int app_dbus_end(void) {

    // stop dbus signal thread
    end_program = true;

    struct timespec tim;
    tim.tv_sec = 1;
    tim.tv_nsec = 0;

    if (nanosleep(&tim, NULL) < 0) {
        log_message(LOG_DEBUG, "Nano sleep system call failed.\n");
    }

    if (pthread_join(app_signal_thread_id, NULL) != 0) {
        log_message(LOG_DEBUG, "App signal thread join failed.\n");
        return -1;
    }

    sd_bus_unref(bus);
    return 0;
}


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

    // Update OD
    app_writeOD(0x3101, 1, &declination, sizeof(declination));
    app_writeOD(0x3101, 2, &right_ascension, sizeof(right_ascension));
    app_writeOD(0x3101, 3, &orientation, sizeof(orientation));
    app_writeOD(0x3101, 4, &timestamp, sizeof(timestamp));
    app_writeOD(0x3102, 0, solve_path, strlen(solve_path));

    // Free memory
    if (solve_path != NULL) {
        free(solve_path);
        solve_path = NULL;
    }

    return 0;
}


static void* app_signal_thread(void* arg) {
    int r;
    sd_bus_error err = SD_BUS_ERROR_NULL;

    while (end_program == false) {
        // Process requests
        r = sd_bus_process(bus, NULL);
        if (r < 0)
            log_message(LOG_DEBUG, "Failed to process bus.\n");
        else if (r > 0) // we processed a request, try to process another one, right-away
            continue;

        // Wait for the next request to process
        if (sd_bus_wait(bus, 100000) < 0)
            log_message(LOG_DEBUG, "Bus wait failed.\n");
    }

    sd_bus_error_free(&err);
    return NULL;
}

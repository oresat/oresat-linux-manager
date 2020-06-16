/**
 * App for the that allow access to the object dictionary thru dbus for testing/debugging.
 *
 * @file        OD_app.c
 * @ingroup     OD_app
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "log_message.h"
#include "app_OD_helpers.h"
#include "file_transfer.h"
#include "app_dbus_controller.h"
#include "OD_app.h"
#include <systemd/sd-bus.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


/** Dbus destionation for OD connection */
#define DESTINATION         "org.OreSat.ObjectDictionary"
/** Dbus interface name for OD connection */
#define INTERFACE_NAME      "org.OreSat.ObjectDictionary"
/** Dbus object path for OD connection */
#define OBJECT_PATH         "/org/OreSat/ObjectDictionary"
/** App's name */
#define APP_NAME            "Obect Dictionary"


static int read_OD(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);
static int write_OD(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);


/** dbus method table */
static const sd_bus_vtable method_vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_METHOD("Read", "qq", "iay", read_OD, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_METHOD("Write", "qqiay", "i", write_OD, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_VTABLE_END
};


static int
read_OD(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    int r;
    uint16_t index, subindex, buf_len = 0;
    uint8_t *buf = NULL;

    // get data
    r = sd_bus_message_read(m, "qq", &index, &subindex);
    if(r < 0) {
        printf("Failed to parse parameters\n");
    }

    // read from OD
    r = app_OD_read(index, subindex, buf, &buf_len);
    if(r != 0) {
        printf("Failed to read from OD\n");
    }

    // send buffer
    return sd_bus_reply_method_return(m, "qay", &buf_len, buf);
}


static int
write_OD(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    int r;
    uint16_t index, subindex, OD_len, buf_len;
    int8_t *buf = NULL;

    r = sd_bus_message_read(m, "qqiay", &index, &subindex, &buf_len, buf);
    if(r < 0) {
        printf("Failed to parse parameters\n");
    }

    // get size
    OD_len = app_OD_get_length(index, subindex);
    if(OD_len < 0) {
        printf("Failed to parse parameters\n");
    }
    if(OD_len < buf_len) {
        printf("Data will not fit\n");
    }

    //write from OD
    r = app_OD_write(index, subindex,buf, buf_len);
    if(r != 0) {
        printf("Failed to write to OD\n");
    }

    // send buffer
    return sd_bus_reply_method_return(m, "s", "done");
}


void
OD_app_thread() {
    sd_bus_slot *slot = NULL;
    sd_bus *bus = NULL;
    bool running = true;
    int r;

    // Connect to the bus
    r = sd_bus_open_system(&bus);
    printf("Failed to connect to system bus\n");

    // Take a well-known service name so that clients can find us
    r = sd_bus_request_name(bus, DESTINATION, SD_BUS_NAME_ALLOW_REPLACEMENT);
    if(r < 0) {
        printf("Failed to acquire service name\n");
    }

    // Install the vtable
    r = sd_bus_add_object_vtable(
            bus,
            &slot,
            OBJECT_PATH,
            INTERFACE_NAME,
            method_vtable,
            &running);
    if(r < 0) {
        printf("Failed to add vtable\n");
    }

    while(running) {
        // Process requests
        r = sd_bus_process(bus, NULL);
        if(r < 0) {
            printf("Failed to process bus\n");
        }

        if (r > 0) // we processed a request, try to process another one, right-away
            continue;

        // Wait for the next request to process
        r = sd_bus_wait(bus, (uint64_t) -1);
        if(r < 0) {
            printf("Failed to wait on bus\n");
        }
    }

    r = sd_bus_release_name(bus, DESTINATION);
    if(r < 0) {
        printf("Failed to release service name\n");
    }

    sd_bus_slot_unref(slot);
    sd_bus_unref(bus);
}


int
setup_OD_app() {
    return 0;
}

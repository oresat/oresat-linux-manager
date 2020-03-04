#include "app_OD_helpers.h"
#include "file_transfer_ODF.h"
#include "application.h"
#include <systemd/sd-bus.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define DESTINATION     "org.OreSat.CirrusFluxCamera"
#define INTERFACE_NAME  "org.OreSat.CirrusFluxCamera"
#define OBJECT_PATH     "/org/OreSat/CirrusFluxCamera"
#define APP_NAME        "CirrusFluxCamera"


// Static variables
static sd_bus           *bus = NULL;
static bool             running = false;


// Static functions headers
CO_SDO_abortCode_t CFC_ODF(CO_ODF_arg_t *ODF_arg);


/*****************************************************************************/
// app ODF and dbus functions


int main_process_ODF_setup(void) {
    app_OD_configure(0x3100, CFC_ODF, NULL, 0, 0U);
    return 0;
}


int main_process_dbus_main(void) {
    int r;

    // Connect to the bus
    r = sd_bus_open_system(&bus);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Failed to connect to systemd bus.\n");
        return r;
    }

    running = true;
    while (running) {
        // Process requests
        r = sd_bus_process(bus, NULL);
        if(r < 0)
            app_log_message(APP_NAME, LOG_DEBUG, "Failed to process bus.\n");
        else if(r > 0) // we processed a request, try to process another one, right-away
            continue;

        // Wait for the next request to process
        if(sd_bus_wait(bus, (uint64_t) -1))
            app_log_message(APP_NAME, LOG_DEBUG, "Bus wait failed.\n");
    }

    sd_bus_unref(bus);
    return 0;
}


/*****************************************************************************/
// app callback functions


CO_SDO_abortCode_t CFC_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *m = NULL;
    uint8_t temp = 0;
    char *file_path;
    int r;

    if(!running) {
        app_log_message(APP_NAME, LOG_DEBUG, "DBus interface is not up for CFC_ODF.");
        return CO_SDO_AB_GENERAL;
    }

    if(ODF_arg->reading == false) { /* write parameters */
        ODF_arg->dataLength = sizeof(temp);
        memcpy(ODF_arg->data, &temp, ODF_arg->dataLength);
    }

    /* Issue the method call and store the response message in m */
    r = sd_bus_call_method(
            bus,
            DESTINATION,
            OBJECT_PATH,
            INTERFACE_NAME,
            "LatestImage",
            &err,
            &m,
            NULL);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_DEBUG, "Failed to issue LatestImage method call.");
        return CO_SDO_AB_GENERAL;
    }

    /* Parse the response message */
    r = sd_bus_message_read(m, "s", &file_path);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_DEBUG, "Failed to parse response message from LatestImage.");
        return CO_SDO_AB_GENERAL;
    }

    if(file_path != NULL)
        app_send_file(file_path);

    sd_bus_error_free(&err);
    sd_bus_message_unref(m);

    ODF_arg->lastSegment = true;

    return ret;
}


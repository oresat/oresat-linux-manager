#include "CANopen.h"
#include "CO_SDO.h"
#include "OD_helpers.h"
#include "file_transfer_ODF.h"
#include "log_message.h"
#include "application.h"
#include <systemd/sd-bus.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define DESTINATION     "org.OreSat.CirrusFluxCamera"
#define INTERFACE_NAME  "org.OreSat.CirrusFluxCamera"
#define OBJECT_PATH     "/org/OreSat/CirrusFluxCamera"


// ***************************************************************************
// app dbus functions


int app_dbus_setup(void) {

    CO_OD_configure(CO->SDO[0], 0x3100, CFC_ODF, NULL, 0, 0U);

    return 0;
}


int app_dbus_end(void) {
    return 0;
}


// ***************************************************************************
// other cirrus flux camera functions


CO_SDO_abortCode_t CFC_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *m = NULL;
    sd_bus  *bus = NULL;
    uint8_t temp = 0;
    char *file_path;
    int r;

    if(ODF_arg->reading == false) { /* write parameters */
        ODF_arg->dataLength = sizeof(temp);
        memcpy(ODF_arg->data, &temp, ODF_arg->dataLength);
    }

    /* Connect to the bus */
    r = sd_bus_open_system(&bus);
    if (r < 0) {
        log_message(LOG_ERR, "Failed to connect to systemd bus.\n");
        return CO_SDO_AB_GENERAL;
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
        log_message(LOG_ERR, "Failed to issue LatestImage method call.");
        return CO_SDO_AB_GENERAL;
    }

    /* Parse the response message */
    r = sd_bus_message_read(m, "s", &file_path);
    if (r < 0) {
        log_message(LOG_ERR, "Failed to parse response message from LatestImage.");
        return CO_SDO_AB_GENERAL;
    }

    if(file_path != NULL)
        app_send_file(file_path);
    else
        log_message(LOG_ERR, "File path was null.");

    sd_bus_error_free(&err);
    sd_bus_message_unref(m);
    sd_bus_unref(bus);

    ODF_arg->lastSegment = true;

    return ret;
}


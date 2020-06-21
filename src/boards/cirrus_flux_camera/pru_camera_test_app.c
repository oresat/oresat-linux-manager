#include "app_include.h"
#include "pru_camera_test_app.h"
#include <systemd/sd-bus.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define DESTINATION     "org.OreSat.CirrusFluxCamera"
#define INTERFACE_NAME  "org.OreSat.CirrusFluxCamera"
#define OBJECT_PATH     "/org/OreSat/CirrusFluxCamera"
#define APP_NAME        "CirrusFluxCamera"


CO_SDO_abortCode_t PRU_CAMERA_TEST_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *m = NULL;
    uint8_t temp = 0;
    char *file_path;
    int r;

    if(ODF_arg->reading == false) { /* write parameters */
        ODF_arg->dataLength = sizeof(temp);
        memcpy(ODF_arg->data, &temp, ODF_arg->dataLength);
    }

    /* Issue the method call and store the response message in m */
    r = sd_bus_call_method(
            APP_DBUS.bus,
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
    else
        app_log_message(APP_NAME, LOG_ERR, "File path was null.");

    ODF_arg->lastSegment = true;

    sd_bus_error_free(&err);
    sd_bus_message_unref(m);
    return ret;
}


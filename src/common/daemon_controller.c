#include "CANopen.h"
#include "CO_driver.h"
#include "app_OD_helpers.h"
#include "daemon_controller.h"
#include <systemd/sd-bus.h>


int systemd_app_setup(void) {

    CO_OD_configure(CO->SDO[0], 0x3000, systemd_ODF, NULL, 0, 0U);

    return 0;
}


CO_SDO_abortCode_t systemd_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    sd_bus_error error = SD_BUS_ERROR_NULL;
    sd_bus *bus = NULL;

    // can't read parameters, write only
    if (ODF_arg->reading == true) {
        return CO_SDO_AB_WRITEONLY;
    }

    switch (ODF_arg->subIndex) {
        case 1 :
            break;

        case 2 :

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    sd_bus_error_free(&error);
    sd_bus_unref(bus);
    return ret;
}


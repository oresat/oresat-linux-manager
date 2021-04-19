#include "CANopen.h"
#include "ecss_time.h"

CO_SDO_abortCode_t
time_producer_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;

    if (ODF_arg->reading)
        get_time_scet((time_scet_t*)ODF_arg->data);
    else
        ret = CO_SDO_AB_READONLY;

    return ret;
}

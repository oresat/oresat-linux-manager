#include "CANopen.h"
#include "ecss_time.h"

CO_SDO_abortCode_t
ecss_scet_odf(CO_ODF_arg_t *ODF_arg) {

    if (ODF_arg->reading)
        get_time_scet((time_scet_t *)ODF_arg->data);
    else
        set_time_scet((time_scet_t *)ODF_arg->data);

    return CO_SDO_AB_NONE;
}

CO_SDO_abortCode_t
ecss_utc_odf(CO_ODF_arg_t *ODF_arg) {

    if (ODF_arg->reading)
        get_time_utc((time_utc_t *)ODF_arg->data);
    else
        set_time_utc((time_utc_t *)ODF_arg->data);

    return CO_SDO_AB_NONE;
}

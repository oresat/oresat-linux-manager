#ifndef TIME_SYNC_H
#define TIME_SYNC_H

#include "CANopen.h"
#include "ecss_time.h"

CO_SDO_abortCode_t ecss_scet_odf(CO_ODF_arg_t *ODF_arg);

CO_SDO_abortCode_t ecss_utc_odf(CO_ODF_arg_t *ODF_arg);

#endif /*TIME_SYNC_H*/

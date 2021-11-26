#ifndef ECSS_TIME_H
#define ECSS_TIME_H

#include <stdint.h>
#include <sys/time.h>

/* CCSDS Unsegmented Time Code (CUC) data type */
typedef union {
    uint64_t raw;
    struct {
        uint32_t coarse : 32;
        uint32_t fine   : 24; // sub seconds
    };
} time_scet_t;

/* CCSDS Day Segmented Time Code (CDS) data type */
typedef union {
    uint64_t raw;
    struct {
        uint16_t day : 16;
        uint32_t ms  : 32;
        uint16_t us  : 16;
    };
} time_utc_t;

/** Gets the local time in SCET format */
void get_time_scet(time_scet_t *scet);

/** Sets the local time from a SCET format */
void set_time_scet(const time_scet_t *scet);

/** Gets the local time in CCSDS UTC format */
void get_time_utc(time_utc_t *utc);

/** Sets the local time from a CCSDS UTC format */
void set_time_utc(const time_utc_t *utc);

#endif /*ECSS_TIME_H*/

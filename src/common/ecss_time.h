/**
 * ECSS SpaceCraft Elapsed Time (SCET) and spacecraft Universal Time
 * Coordinated (UTC) time code formats.
 *
 * @file        ecss_time.c
 * @ingroup     ecss_time
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef ECSS_TIME_H
#define ECSS_TIME_H

#include <stdint.h>

/** ECSS SCET data type */
typedef union {
    uint64_t raw;
    struct {
        uint32_t coarse : 32; // seconds
        uint32_t fine   : 24; // sub-seconds
    };
} time_scet_t;

/** ECSS UTC data type */
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

/** Gets the local time in ECSS UTC format */
void get_time_utc(time_utc_t *utc);

/** Sets the local time from a ECSS UTC format */
void set_time_utc(const time_utc_t *utc);

#endif /* ECSS_TIME_H */

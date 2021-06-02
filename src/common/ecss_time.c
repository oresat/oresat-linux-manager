#include "ecss_time.h"
#include "logging.h"
#include <stddef.h>
#include <sys/time.h>

#define SECS_IN_DAY (24 * 60 * 60)

void
get_time_scet(time_scet_t *scet) {
    struct timeval time;

    if (scet == NULL)
        return;

    gettimeofday(&time, NULL);

    scet->coarse = time.tv_sec;
    scet->fine   = time.tv_usec;
}

void
set_time_scet(const time_scet_t *scet) {
    struct timeval time;

    if (scet == NULL)
        return;

    time.tv_sec  = scet->coarse;
    time.tv_usec = scet->fine;

    log_printf(LOG_INFO, "SCET setting time to %d.%d", time.tv_sec,
               time.tv_usec);
    settimeofday(&time, NULL);
}

void
get_time_utc(time_utc_t *utc) {
    struct timeval time;

    if (utc == NULL)
        return;

    gettimeofday(&time, NULL);

    utc->day = time.tv_sec / SECS_IN_DAY;
    utc->ms  = time.tv_usec / 1000;
    utc->us  = time.tv_usec % 1000;
}

void
set_time_utc(const time_utc_t *utc) {
    struct timeval time;

    if (utc == NULL)
        return;

    time.tv_sec  = utc->day * SECS_IN_DAY;
    time.tv_usec = utc->ms * 1000 + utc->us;

    log_printf(LOG_INFO, "UTC setting time to %d.%d", time.tv_sec,
               time.tv_usec);
    settimeofday(&time, NULL);
}

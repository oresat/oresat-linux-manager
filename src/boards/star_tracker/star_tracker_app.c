
#include "CANopen.h"
#include "ecss_time.h"
#include "olm_file_cache.h"
#include "star_tracker.h"
#include "star_tracker_app.h"
#include <stdint.h>

void
star_tracker_app_async(void *data, olm_file_cache_t *fread_cache) {
    st_coordinates_t coor;
    time_scet_t time;

    if (star_tracker_coordinates(&coor) >= 0) {
        time.coarse = coor.timestamp.tv_sec;
        time.fine = coor.timestamp.tv_usec;

        CO_LOCK_OD();
        OD_orienation.rightAscension = (int16_t)coor.right_ascension;
        OD_orienation.declination = (int16_t)coor.declination;
        OD_orienation.roll = (int16_t)coor.roll;
        OD_orienation.timestamp = time.raw;
        CO_UNLOCK_OD();
    }
}

void
star_tracker_app_end(void *data) {
    CO_LOCK_OD();
    OD_starTrackerStatus = 0xFF;
    CO_UNLOCK_OD();
}

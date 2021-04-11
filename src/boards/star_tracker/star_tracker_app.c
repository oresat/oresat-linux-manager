
#include "CANopen.h"
#include "olm_file_cache.h"
#include "star_tracker.h"
#include "star_tracker_app.h"

void
star_tracker_app_async(void *data, olm_file_cache_t *fread_cache) {
    st_coordinates_t coor;

    if (star_tracker_coordinates(&coor) >= 0) {
        CO_LOCK_OD();
        OD_orienation.rightAscension = coor.right_ascension;
        OD_orienation.declination = coor.declination;
        OD_orienation.roll = coor.roll;
        OD_orienation.timestamp = 0; // TODO fix
        CO_UNLOCK_OD();
    } else {
        CO_LOCK_OD();
        OD_orienation.rightAscension = 0;
        OD_orienation.declination = 0;
        OD_orienation.roll = 0;
        OD_orienation.timestamp = 0;
        CO_UNLOCK_OD();
    }
}

void
star_tracker_app_end(void *data) {
        CO_LOCK_OD();
        OD_starTrackerStatus = 0xFF;
        CO_UNLOCK_OD();
}

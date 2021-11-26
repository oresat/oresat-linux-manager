/**
 * OreSat GPS app.
 *
 * @file        gps_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "gps_app.h"
#include "CANopen.h"
#include "ecss_time.h"
#include "gps.h"
#include "object_dictionary/CO_OD.h"
#include "olm_file_cache.h"
#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>

#define TPDO_GPS_SV_TIME  2
#define TPDO_GPS_SV_X_Y   3
#define TPDO_GPS_SV_Z_VX  4
#define TPDO_GPS_SV_VY_VZ 5
#define TPDO_GPS_GENERAL  6

void
gps_app_async(void *data, olm_file_cache_t *fread_cache) {
    state_vector_t sv;
    time_scet_t time;
    uint8_t state, sats;

    if (!CO->TPDO[TPDO_GPS_GENERAL]->valid) {
        CO_LOCK_OD();
        CO->TPDO[TPDO_GPS_GENERAL]->valid = true;
        CO_UNLOCK_OD();
    }

    if (gps_time_synchronized() && !OD_timeSynchronized) {
        CO_LOCK_OD();
        OD_timeSynchronized = true;
        CO_UNLOCK_OD();
    }

    state = gps_status();
    sats = gps_satellite_number();

    if (state != 0xFF) {
        CO_LOCK_OD();
        OD_GPSStatus = state;
        OD_satellitesLocked = sats;
        CO->TPDO[TPDO_GPS_SV_TIME]->valid = true;
        CO->TPDO[TPDO_GPS_SV_X_Y]->valid = true;
        CO->TPDO[TPDO_GPS_SV_Z_VX]->valid = true;
        CO->TPDO[TPDO_GPS_SV_VY_VZ]->valid = true;
        CO_UNLOCK_OD();
    } else {
        CO_LOCK_OD();
        OD_GPSStatus = state;
        OD_satellitesLocked = sats;
        CO->TPDO[TPDO_GPS_SV_TIME]->valid = false;
        CO->TPDO[TPDO_GPS_SV_X_Y]->valid = false;
        CO->TPDO[TPDO_GPS_SV_Z_VX]->valid = false;
        CO->TPDO[TPDO_GPS_SV_VY_VZ]->valid = false;
        CO_UNLOCK_OD();
        return; // state vector is invalid
    }

    if (state == 0x2 && gps_state_vector(&sv) >= 0) {
        time.coarse = sv.timestamp.tv_sec;
        time.fine = sv.timestamp.tv_usec;

        CO_LOCK_OD();
        OD_stateVector.positionX = sv.position.x;
        OD_stateVector.positionY = sv.position.y;
        OD_stateVector.positionZ = sv.position.z;
        OD_stateVector.velocityX = sv.velocity.x;
        OD_stateVector.velocityY = sv.velocity.y;
        OD_stateVector.velocityZ = sv.velocity.z;
        OD_stateVector.timeStamp = time.raw;
        CO_UNLOCK_OD();
    }
}

void
gps_app_end(void *data) {
    CO_LOCK_OD();
    CO->TPDO[TPDO_GPS_SV_TIME]->valid = false;
    CO->TPDO[TPDO_GPS_SV_X_Y]->valid = false;
    CO->TPDO[TPDO_GPS_SV_Z_VX]->valid = false;
    CO->TPDO[TPDO_GPS_SV_VY_VZ]->valid = false;
    CO->TPDO[TPDO_GPS_GENERAL]->valid = false;
    OD_GPSStatus = 0xFF;
    OD_satellitesLocked = 0;
    CO_UNLOCK_OD();
}

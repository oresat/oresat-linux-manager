/**
 * Module for interfacing with the OreSat GPS daemon over D-Bus.
 *
 * @file        gps.c
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef GPS_MODULE_H
#define GPS_MODULE_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>

#define GPS_SERVICE_FILE "oresat-gpsd.service"

enum gps_states {
    GPS_SEARCHING = 0x00,
    GPS_LOCKED = 0x01,
    GPS_HARDWARE_ERROR = 0x02,
    GPS_PARSER_ERROR = 0x03,
    GPS_UNKNOWN = 0xFF, // most likely it is off
};

typedef struct {
    int32_t x;
    int32_t y;
    int32_t z;
} xyz_t;

typedef struct {
    xyz_t position;
    xyz_t velocity;
    struct timeval timestamp;
} state_vector_t;

/**
 * @brief Get the current state vector.
 *
 * @parm st the struct to fill out
 *
 * @return non negative number on error.
 */
int
gps_state_vector(state_vector_t *st);

/**
 * @brief get the status of oresat-gpsd
 *
 * @return A @ref gps_states value.
 */
uint8_t
gps_status(void);

/**
 * @brief Flag if the local time has been synchronized with gps time
 *
 * @return true if the local time has been synchronized.
 */
bool
gps_time_synchronized(void);

/**
 * @brief get the number of satellites that are locked onto.
 *
 * @return Number of satellites locked onto (max 12).
 */
uint8_t
gps_satellite_number(void);

#endif /* GPS_MODULE_H */

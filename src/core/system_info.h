/**
 * System information ODF.
 *
 * @file        system_info.h
 * @ingroup     system_info
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux systems.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include "CANopen.h"
#include <stdbool.h>
#include <stdint.h>

/** Private data for system info ODF to use */
typedef struct {
    /** Hostname */
    char *hostname;
    /** OS */
    char *os_name;
    /** OS distro */
    char *os_distro;
    /** Kernel version */
    char *kernel_version;
    /** Architecture */
    char *architecture;
    /** current remoteproc selected */
    uint8_t rproc;
} system_info_t;

/**
 * Create a system_info_t object
 *
 * @see system_info_destroy
 */
system_info_t *system_info_create(void);

/**
 * Destroy system_info_t object.
 *
 * @param info the system_info_t object to free
 *
 * @see system_info_create
 */
void system_info_destroy(system_info_t *info);

/**
 * Callback for using inside CO_OD_configure() function for getting the systems
 * info.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t system_info_ODF(CO_ODF_arg_t *ODF_arg);

#endif /* SYSTEM_INFO_H */

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
    /** Flag for 1st time accessed */
    bool init;
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
} system_info_t;

#define SYSTEM_INFO_DEFAULT                                                    \
    {                                                                          \
        .init = true, .hostname = NULL, .os_name = NULL, .os_distro = NULL,    \
        .kernel_version = NULL, .architecture = NULL,                          \
    }

/** Free all data in a @ref system_info_t object. */
void system_info_free(system_info_t *info);

void system_info_async(system_info_t *info);

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

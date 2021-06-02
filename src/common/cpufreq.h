/**
 * Simple function that allow OLM to get and control the CPU frequency.
 *
 * @file        cpufreq.h
 * @ingroup     cpufreq
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef CPUFREQ_H
#define CPUFREQ_H

#include <stdint.h>

enum cpu_gov {
    unknown     = 0,
    powersave   = 1,
    performance = 2,
};

/**
 * Gets current cpu freqency in MHz.
 *
 * @return cpufreq on success or 0 on error.
 */
uint32_t
get_cpufreq(void);

/**
 * Gets cpufreq governor.
 *
 * @return cpu_gov enum value on success or -1 on error.
 */
int
get_cpufreq_gov(void);

/**
 * Sets cpufreq governor.
 *
 * @return 0 on success or negative errno value on error.
 */
int
set_cpufreq_gov(int governor);

#endif

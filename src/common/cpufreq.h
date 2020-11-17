#include <stdint.h>


#ifndef CPUFREQ_H
#define CPUFREQ_H


/**
 * Gets current cpu freqency.
 * @returns cpufreq on success or 0 on error.
 */
uint32_t get_cpufreq(void);


/**
 * Sets cpufreq to maximum.
 * @returns 0 on success or negative errno value on error.
 */
int set_cpufreq_max(void);


/**
 * Sets cpufreq to minimum.
 * @returns 0 on success or negative errno value on error.
 */
int set_cpufreq_min(void);


#endif

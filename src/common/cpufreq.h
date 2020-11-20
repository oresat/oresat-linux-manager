#include <stdint.h>


#ifndef CPUFREQ_H
#define CPUFREQ_H


enum cpu_gov {
    unknown = 0,
    powersave = 1,
    performance = 2,
};


/**
 * Gets current cpu freqency in MHz. 
 *
 * @return cpufreq on success or 0 on error.
 */
uint32_t get_cpufreq(void);


/**
 * Gets cpufreq governor.
 *
 * @return cpu_gov enum value on success or -1 on error.
 */
int get_cpufreq_gov(void);


/**
 * Sets cpufreq governor.
 *
 * @return 0 on success or negative errno value on error.
 */
int set_cpufreq_gov(int governor);


#endif

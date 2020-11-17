#include "cpufreq.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>


#define FILEPATH            "/sys/devices/system/cpu/cpufreq/policy0/"
#define SETFREQ_FILE        FILEPATH"scaling_setspeed"
#define CURFREQ_FILE        FILEPATH"scaling_cur_freq"
#define GOV_FILE            FILEPATH"scaling_governor"
#define CPUFREQ_MAX_FILE    FILEPATH"set_cpufreq_max"
#define CPUFREQ_MIN_FILE    FILEPATH"set_cpufreq_min"


/** the maximum CPU freqency, set by get_cpufreq_min_max() */
static uint32_t cpufreq_max = 0;
/** the minimum CPU freqency, set by get_cpufreq_min_max() */
static uint32_t cpufreq_min = 0;


static int get_cpufreq_min_max(void);
static int get_sysfs_int(char *filepath, uint32_t *value);
static int set_gov_userspace(void);


/**
 * Get the interger value from a sysfs file
 * @param filepath The path to sysfs file.
 * @param value A pointer to the value to overwrite.
 * @returns 0 on success or negative errno value on error.
 */
static int
get_sysfs_int(char *filepath, uint32_t *value) {
    FILE* fptr = NULL;
    int r = 0;

    fptr = fopen(filepath, "r");
    if(fptr != NULL) {
        if(fscanf(fptr, "%d", value) == EOF)
            r = -ENOENT;
        if(fclose(fptr) != 0)
            r = -EBADF;
    }
    else
        r = -EIO;

    return r;
}


/**
 * Set local cpufreq min and max variables
 * @returns 0 on success or negative errno value on error.
 */
static int
get_cpufreq_min_max(void) {
    int r = 0;

    if(cpufreq_max != 0 && cpufreq_min != 0)
        return r; // no need to set local variables

    if((r = get_sysfs_int(CPUFREQ_MAX_FILE, &cpufreq_max)) != 0)
        return r;

    if((r = get_sysfs_int(CPUFREQ_MIN_FILE, &cpufreq_min)) != 0)
        return r;

    return 0;
}


/**
 * Sets the governor to "userspace"
 * @returns 0 on succes or negative errno on error.
 */
static int
set_gov_userspace(void) {
    FILE *fptr = NULL;
    char *mode = NULL;
    char user_mode[] = "userspace";

    // check current governor
    if((fptr = fopen(GOV_FILE, "r")) != NULL) {
        fscanf(fptr, "%s", mode);
        fclose(fptr);
    }
    else 
        return -ENOENT;

    // set mode to userspace if not
    if(strncmp(mode, user_mode, strlen(mode)+1)) {
        if((fptr = fopen(GOV_FILE, "w")) != NULL) {
            fputs(user_mode, fptr);
            fclose(fptr);
        }
        else
            return -ENOENT;
    }

    return 0;
}


uint32_t
get_cpufreq(void) {
    uint32_t cpufreq = 0;

    if(get_sysfs_int(CURFREQ_FILE, &cpufreq) != 0)
        return 0;

    return cpufreq;
}


int 
set_cpufreq_max(void) {
    FILE* fptr = NULL;
    int r = 0;

    if((r = get_cpufreq_min_max()) != 0)
        return r;

    if((r = set_gov_userspace()) != 0)
        return r;

    // set cpu to min
    if((fptr = fopen(SETFREQ_FILE, "w")) != NULL) { 
        fprintf(fptr, "%d", cpufreq_max);
        fclose(fptr);
    }
    else
        r = -EIO;

    return r;
}


int
set_cpufreq_min(void) {
    FILE *fptr = NULL;
    int r = 0;

    if((r = get_cpufreq_min_max()) != 0)
        return r;

    if((r = set_gov_userspace()) != 0)
        return r;

    // set cpu to max
    if((fptr = fopen(SETFREQ_FILE, "w")) != NULL) {
        fprintf(fptr, "%d", cpufreq_min);
        fclose(fptr);
    }
    else
        r = -EIO;

    return r;
}

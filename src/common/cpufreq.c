/**
 * Simple function that allow OLM to get and control the CPU frequency.
 *
 * @file        cpufreq.c
 * @ingroup     cpufreq
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "cpufreq.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** filepath to cpu sysfs files */
#define FILEPATH     "/sys/devices/system/cpu/cpufreq/policy0/"
/** filepath to a cpu frequency sysfs file */
#define CURFREQ_FILE FILEPATH "scaling_cur_freq"
/** filepath to a cpu governor sysfs file */
#define GOV_FILE     FILEPATH "scaling_governor"

unsigned int
get_cpufreq(void) {
    FILE *fptr = NULL;
    int buf_len = 50;
    char buf[buf_len];
    int r = 0;

    fptr = fopen(CURFREQ_FILE, "r");
    if (fptr != NULL) {
        fgets(buf, buf_len, fptr);
        fclose(fptr);
        r = strtol(buf, NULL, 10) / 1000;
    }

    return r;
}

int
get_cpufreq_gov(void) {
    FILE *fptr = NULL;
    int buf_len = 50;
    char buf[buf_len];
    int r = 0;

    if ((fptr = fopen(GOV_FILE, "r")) != NULL) {
        fgets(buf, buf_len, fptr);
        fclose(fptr);
    }

    if (strncmp(buf, "powersave", strlen("powersave")) == 0)
        r = CPUFREQ_GOV_POWERSAVE;
    else if (strncmp(buf, "performance", strlen("performance")) == 0)
        r = CPUFREQ_GOV_PERFORMACE;
    else
        r = CPUFREQ_GOV_UNKNOWN;

    return r;
}

int
set_cpufreq_gov(int governor) {
    FILE *fptr = NULL;
    int r = 0;

    if ((fptr = fopen(GOV_FILE, "w")) == NULL)
        return -EIO;

    switch (governor) {
    case CPUFREQ_GOV_POWERSAVE:
        fwrite("powersave", 1, strlen("powersave") + 1, fptr);
        break;

    case CPUFREQ_GOV_PERFORMACE:
        fwrite("performance", 1, strlen("performance") + 1, fptr);
        break;

    default:
        r = -EINVAL;
    }

    fclose(fptr);

    return r;
}

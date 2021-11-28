/**
 * System information ODF.
 *
 * @file        system_info.c
 * @ingroup     system_info
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux systems.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "system_info.h"
#include "301/CO_SDOserver.h"
#include "301/CO_driver.h"
#include "CANopen.h"
#include "CO_OD.h"
#include "cpufreq.h"
#include "logging.h"
#include "utility.h"
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

/** filepath remoteproc directory */
#define REMOTEPROC_DIR "/sys/class/remoteproc/"

#define MEGABYTE       (1024 * 1024)

// see function definition for doxygen comments
static int get_linux_distro_name(char *buf, int buf_len);
static int get_nremoteprocs(void);

system_info_t *
system_info_create(void) {
    system_info_t *info;
    struct utsname name;
    int buf_len = 256;
    char buf[buf_len];
    int len;

    info = malloc(sizeof(system_info_t));
    if (!info)
        return info;

    if (uname(&name) == 0) {
        // os name
        len = strlen(name.sysname) + 1;
        info->os_name = malloc(len);
        if (info->os_name)
            strncpy(info->os_name, name.sysname, len);
        else
            log_printf(LOG_CRIT, "malloc failed for os_distro");

        // kernel version
        len = strlen(name.release) + 1;
        info->kernel_version = malloc(len);
        if (info->kernel_version)
            strncpy(info->kernel_version, name.release, len);
        else
            log_printf(LOG_CRIT, "malloc failed for kernel_version");

        // hostname
        len = strlen(name.nodename) + 1;
        info->hostname = malloc(len);
        if (info->hostname)
            strncpy(info->hostname, name.nodename, len);
        else
            log_printf(LOG_CRIT, "malloc failed for hostname");

        // architecture
        len = strlen(name.machine) + 1;
        info->architecture = malloc(len);
        if (info->architecture)
            strncpy(info->architecture, name.machine, len);
        else
            log_printf(LOG_CRIT, "malloc failed for architecture");
    }

    // os distro name
    if (get_linux_distro_name(buf, buf_len) == 0) {
        len = strlen(buf) + 1;
        info->os_distro = malloc(len * sizeof(char));
        strncpy(info->os_distro, buf, len);
    }

    info->rproc = 0;

    return info;
}

void
system_info_destroy(system_info_t *info) {
    if (info) {
        FREE(info->os_distro);
        FREE(info->kernel_version);
        FREE(info->hostname);
        FREE(info->architecture);
        FREE(info->os_name);
        free(info);
    }
}

CO_SDO_abortCode_t
system_info_ODF(CO_ODF_arg_t *ODF_arg) {
    assert(ODF_arg->object);
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    system_info_t *data = (system_info_t *)ODF_arg->object;
    FILE *fptr = NULL;
    int buf_len = 256;
    char filepath[PATH_MAX], buf[buf_len];
    struct sysinfo info;
    struct statvfs fs_info;

    // every subindex is readonly except the remoteprocX selector subindex is
    // readwrite
    if (!ODF_arg->reading
        && ODF_arg->subIndex != OD_3001_11_systemInfo_remoteprocXSelector)
        return CO_SDO_AB_READONLY;

    switch (ODF_arg->subIndex) {
    case OD_3001_1_systemInfo_OSName:
        ODF_arg->dataLength = strlen(data->os_name) + 1;
        memcpy(ODF_arg->data, data->os_name, ODF_arg->dataLength);
        break;

    case OD_3001_2_systemInfo_OSDistro:
        ODF_arg->dataLength = strlen(data->os_distro) + 1;
        memcpy(ODF_arg->data, data->os_distro, ODF_arg->dataLength);
        break;

    case OD_3001_3_systemInfo_OSKernelVersion:
        ODF_arg->dataLength = strlen(data->kernel_version) + 1;
        memcpy(ODF_arg->data, data->kernel_version, ODF_arg->dataLength);
        break;

    case OD_3001_4_systemInfo_hostname:
        ODF_arg->dataLength = strlen(data->hostname) + 1;
        memcpy(ODF_arg->data, data->hostname, ODF_arg->dataLength);
        break;

    case OD_3001_5_systemInfo_uptime:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)(info.uptime / 60));
        else
            ret = CO_SDO_AB_DATA_LOC_CTRL;
        break;

    case OD_3001_6_systemInfo_numberOfCPUs:
        CO_setUint8(ODF_arg->data, get_nprocs());
        break;

    case OD_3001_7_systemInfo_CPUArchitecture:
        ODF_arg->dataLength = strlen(data->architecture) + 1;
        memcpy(ODF_arg->data, data->architecture, ODF_arg->dataLength);
        break;

    case OD_3001_8_systemInfo_CPUGovernor:
        CO_setUint8(ODF_arg->data, get_cpufreq_gov());
        break;

    case OD_3001_9_systemInfo_CPUFrequency:
        CO_setUint16(ODF_arg->data, get_cpufreq());
        break;

    case OD_3001_10_systemInfo_numberOfRemoteprocs:
        CO_setUint8(ODF_arg->data, get_nremoteprocs());
        break;

    case OD_3001_11_systemInfo_remoteprocXSelector:
        if (ODF_arg->reading) {
            CO_setUint8(ODF_arg->data, data->rproc);
        } else {
            uint8_t rproc = CO_getUint8(ODF_arg->data);
            if (rproc > OD_systemInfo.numberOfRemoteprocs)
                return CO_SDO_AB_VALUE_HIGH;
            data->rproc = rproc;
        }
        break;

    case OD_3001_12_systemInfo_remoteprocXName:
        sprintf(filepath, REMOTEPROC_DIR "remoteproc%d/state", data->rproc);
        if ((fptr = fopen(filepath, "r")) != NULL) {
            fgets(buf, buf_len, fptr);
            fclose(fptr);
            buf[strlen(buf) - 1] = '\0';
            ODF_arg->dataLength = strlen(buf) + 1;
            memcpy(ODF_arg->data, buf, ODF_arg->dataLength);
        } else { // incase of file not exsiting
            ret = CO_SDO_AB_NO_DATA;
        }
        break;

    case OD_3001_13_systemInfo_remoteprocXState:
        sprintf(filepath, REMOTEPROC_DIR "remoteproc%d/state", data->rproc);
        if ((fptr = fopen(filepath, "r")) != NULL) {
            fgets(buf, buf_len, fptr);
            fclose(fptr);
            buf[strlen(buf) - 1] = '\0';
            ODF_arg->dataLength = strlen(buf) + 1;
            memcpy(ODF_arg->data, buf, ODF_arg->dataLength);
        } else { // incase of file not exsiting
            ret = CO_SDO_AB_NO_DATA;
        }
        break;

    case OD_3001_14_systemInfo_loadAverage1min:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)info.loads[0]);
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_15_systemInfo_loadAverage5min:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)info.loads[1]);
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_16_systemInfo_loadAverage15min:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)info.loads[2]);
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_17_systemInfo_ramTotal:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)(info.totalram / MEGABYTE));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_18_systemInfo_ramFree:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)(info.freeram / MEGABYTE));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_19_systemInfo_ramShared:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)(info.sharedram / MEGABYTE));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_20_systemInfo_ramBuffered:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)(info.bufferram / MEGABYTE));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_21_systemInfo_ramPercent:
        if (sysinfo(&info) != -1)
            CO_setUint8(ODF_arg->data, (uint8_t)((info.totalram - info.freeram)
                                                 * 100 / info.totalram));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_22_systemInfo_swapTotal:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)(info.totalswap / MEGABYTE));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_23_systemInfo_swapFree:
        if (sysinfo(&info) != -1)
            CO_setUint32(ODF_arg->data, (uint32_t)(info.freeswap / MEGABYTE));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_24_systemInfo_swapPercent:
        if (sysinfo(&info) != -1)
            CO_setUint8(ODF_arg->data,
                        (uint8_t)((info.totalswap - info.freeswap) * 100
                                  / info.totalswap));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_25_systemInfo_procs:
        CO_setUint8(ODF_arg->data, get_nprocs());
        break;

    case OD_3001_26_systemInfo_rootParitionTotal:
        if (statvfs("/", &fs_info) == 0)
            // the order help with int overflow on 32bit systems
            CO_setUint32(ODF_arg->data, (uint32_t)(fs_info.f_blocks / 1024
                                                   * fs_info.f_bsize / 1024));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_27_systemInfo_rootParitionFree:
        if (statvfs("/", &fs_info) == 0)
            // the order help with int overflow on 32bit systems
            CO_setUint32(ODF_arg->data, (uint32_t)(fs_info.f_bavail / 1024
                                                   * fs_info.f_bsize / 1024));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;

    case OD_3001_28_systemInfo_rootParitionPercent:
        if (statvfs("/", &fs_info) == 0)
            // the order help with int overflow on 32bit systems
            CO_setUint8(ODF_arg->data,
                        (uint8_t)((fs_info.f_blocks - fs_info.f_bavail) * 100
                                  / fs_info.f_blocks));
        else
            ret = CO_SDO_AB_NO_DATA;
        break;
    }

    return ret;
}

static int
get_linux_distro_name(char *buf, int buf_len) {
    FILE *filePointer;
    bool found = false;
    char *temp = NULL;

    if ((filePointer = fopen("/etc/os-release", "r")) == NULL)
        return -ENOENT;

    while (fgets(buf, buf_len, filePointer)) {
        if (strncmp(buf, "PRETTY_NAME", strlen("PRETTY_NAME")) == 0) {
            found = true;
            break;
        }
    }

    fclose(filePointer);

    if (found != true) {
        buf[0] = '\0';
    } else {
        temp = strrchr(buf, '\"');
        *temp = '\0';
        temp = strchr(buf, '\"');
        strncpy(buf, &temp[1], strlen(temp) + 1);
    }

    return 0;
}

static int
get_nremoteprocs(void) {
    struct stat st = {0};
    struct dirent *dir;
    DIR *d;
    int nremoteproc = 0;

    // make sure dir exist
    if (stat(REMOTEPROC_DIR, &st) == -1) {
        return nremoteproc;
    }

    if ((d = opendir(REMOTEPROC_DIR))
        != NULL) {                           // add all existing file to list
        while ((dir = readdir(d)) != NULL) { // directory found
            if (strncmp(dir->d_name, ".", sizeof(dir->d_name)) == 0
                || strncmp(dir->d_name, "..", sizeof(dir->d_name)) == 0)
                continue; // skip . and ..

            ++nremoteproc;
        }
        closedir(d);
    }

    return nremoteproc;
}

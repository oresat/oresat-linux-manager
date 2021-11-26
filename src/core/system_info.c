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
#include "CANopen.h"
#include "cpufreq.h"
#include "logging.h"
#include "utility.h"
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

// see function definition for doxygen comments
static int get_linux_distro_name(char *buf, int buf_len);
static int get_nremoteprocs(void);
static void system_info_fill(system_info_t *info);

static void
system_info_fill(system_info_t *info) {
    struct utsname name;
    int buf_len = 256;
    char buf[buf_len];
    int len;

    if (!info->init)
        return;

    if (uname(&name) == 0) {
        // os name
        len = strlen(name.sysname) + 1;
        info->os_name = malloc(len * sizeof(char));
        if (info->os_name != NULL)
            strncpy(info->os_name, name.sysname, len);
        else
            log_printf(LOG_CRIT, "malloc failed for os_distro");

        // kernel version
        len = strlen(name.release) + 1;
        info->kernel_version = malloc(len * sizeof(char));
        if (info->kernel_version != NULL)
            strncpy(info->kernel_version, name.release, len);
        else
            log_printf(LOG_CRIT, "malloc failed for kernel_version");

        // hostname
        len = strlen(name.nodename) + 1;
        info->hostname = malloc(len * sizeof(char));
        if (info->hostname != NULL)
            strncpy(info->hostname, name.nodename, len);
        else
            log_printf(LOG_CRIT, "malloc failed for hostname");

        // architecture
        len = strlen(name.machine) + 1;
        info->architecture = malloc(len * sizeof(char));
        if (info->architecture != NULL)
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
}

void
system_info_free(system_info_t *info) {
    FREE(info->os_distro);
    FREE(info->kernel_version);
    FREE(info->hostname);
    FREE(info->architecture);
    FREE(info->os_name);
}

void
system_info_async(system_info_t *data) {
    struct sysinfo info;
    struct statvfs fs_info;

    CO_LOCK_OD();

    if (data->init) {
        system_info_fill(data);

        if (sysinfo(&info) == 0) {
            OD_systemInfo.swapTotal = (uint32_t)(info.totalswap / 1024 / 1024);
            OD_systemInfo.ramTotal = (uint32_t)(info.totalram / 1024 / 1024);
        }

        if (statvfs("/", &fs_info) == 0)
            // the order help with int overflow on 32bit systems
            OD_systemInfo.rootParitionTotal
                = (uint32_t)(fs_info.f_blocks / 1024 * fs_info.f_bsize / 1024);

        OD_systemInfo.numberOfCPUs = get_nprocs();
        OD_systemInfo.numberOfRemoteprocs = get_nremoteprocs();
        OD_systemInfo.CPUGovernor = get_cpufreq_gov();
        OD_systemInfo.CPUFrequency = get_cpufreq();

        data->init = false;
    }

    if (sysinfo(&info) != -1) {
        OD_systemInfo.uptime = (uint32_t)(info.uptime / 60);
        OD_systemInfo.loadAverage1min = (uint32_t)info.loads[0];
        OD_systemInfo.loadAverage5min = (uint32_t)info.loads[1];
        OD_systemInfo.loadAverage15min = (uint32_t)info.loads[2];
        OD_systemInfo.ramFree = (uint32_t)(info.freeram / 1024 / 1024);
        OD_systemInfo.ramShared = (uint32_t)(info.sharedram / 1024 / 1024);
        OD_systemInfo.ramBuffered = (uint32_t)(info.bufferram / 1024 / 1024);
        OD_systemInfo.ramPercent
            = (uint8_t)((info.totalram - info.freeram) * 100 / info.totalram);
        if (OD_systemInfo.swapTotal > 0) {
            OD_systemInfo.swapFree = (uint32_t)(info.freeswap / 1024 / 1024);
            OD_systemInfo.swapPercent
                = (uint8_t)((info.totalswap - info.freeswap) * 100
                            / info.totalswap);
        }
        OD_systemInfo.procs = (uint32_t)info.procs;
    }

    if ((statvfs("/", &fs_info)) == 0) {
        // the order help with int overflow on 32bit systems
        OD_systemInfo.rootParitionFree
            = (uint32_t)(fs_info.f_bavail / 1024 * fs_info.f_bsize / 1024);
        OD_systemInfo.rootParitionPercent
            = (uint8_t)((fs_info.f_blocks - fs_info.f_bavail) * 100
                        / fs_info.f_blocks);
    }

    CO_UNLOCK_OD();
}

CO_SDO_abortCode_t
system_info_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    system_info_t *data = (system_info_t *)ODF_arg->object;
    FILE *fptr = NULL;
    int buf_len = 256;
    char filepath[PATH_MAX], buf[buf_len];

    if (data == NULL)
        return CO_SDO_AB_GENERAL;

    // every subindex is readonly except the remoteprocX selector subindex is
    // readwrite
    if (ODF_arg->reading == false
        && ODF_arg->subIndex != OD_3001_11_systemInfo_remoteprocXSelector)
        return CO_SDO_AB_READONLY;

    switch (ODF_arg->subIndex) {
    case OD_3001_1_systemInfo_OSName: // OS, domain, readonly
        ODF_arg->dataLength = strlen(data->os_name) + 1;
        memcpy(ODF_arg->data, data->os_name, ODF_arg->dataLength);
        break;

    case OD_3001_2_systemInfo_OSDistro: // OS distro, domain, readonly
        ODF_arg->dataLength = strlen(data->os_distro) + 1;
        memcpy(ODF_arg->data, data->os_distro, ODF_arg->dataLength);
        break;

    case OD_3001_3_systemInfo_OSKernelVersion: // kernel version, domain,
                                               // readonly
        ODF_arg->dataLength = strlen(data->kernel_version) + 1;
        memcpy(ODF_arg->data, data->kernel_version, ODF_arg->dataLength);
        break;

    case OD_3001_4_systemInfo_hostname: // hostname, domain, readonly
        ODF_arg->dataLength = strlen(data->hostname) + 1;
        memcpy(ODF_arg->data, data->hostname, ODF_arg->dataLength);
        break;

    case OD_3001_7_systemInfo_CPUArchitecture: // CPU Architecture, domain,
                                               // readonly
        ODF_arg->dataLength = strlen(data->architecture) + 1;
        memcpy(ODF_arg->data, data->architecture, ODF_arg->dataLength);
        break;

    case OD_3001_11_systemInfo_remoteprocXSelector: // RemoteprocX, uint8_t,
                                                    // readwrite
        if (!ODF_arg->reading) {
            if (CO_getUint8(data) > OD_systemInfo.numberOfRemoteprocs)
                return CO_SDO_AB_GENERAL; // TODO
        }
        break;

    case OD_3001_12_systemInfo_remoteprocXName: // RemoteprocX name, domain,
                                                // readonly
        sprintf(filepath, "%sremoteproc%d/name", REMOTEPROC_DIR,
                OD_systemInfo.remoteprocXSelector);
        if ((fptr = fopen(filepath, "r")) != NULL) {
            fgets(buf, buf_len, fptr);
            fclose(fptr);
            buf[strlen(buf) - 1] = '\0';
        } else { // incase of file not exsiting
            return CO_SDO_AB_NO_DATA;
        }

        ODF_arg->dataLength = strlen(buf) + 1;
        memcpy(ODF_arg->data, buf, ODF_arg->dataLength);
        break;

    case OD_3001_13_systemInfo_remoteprocXState: // RemoteprocX state, uint8_t,
                                                 // readonly
        sprintf(filepath, "%sremoteproc%d/state", REMOTEPROC_DIR,
                OD_systemInfo.remoteprocXSelector);
        if ((fptr = fopen(filepath, "r")) != NULL) {
            fgets(buf, buf_len, fptr);
            fclose(fptr);
            buf[strlen(buf) - 1] = '\0';
        } else { // incase of file not exsiting
            return CO_SDO_AB_NO_DATA;
        }

        ODF_arg->dataLength = strlen(buf) + 1;
        memcpy(ODF_arg->data, buf, ODF_arg->dataLength);
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

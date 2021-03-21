/**
 * Board Info Object Dictionary Function.
 *
 * @file        board_info.c
 * @ingroup     board_info
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "CANopen.h"
#include "CO_OD.h"
#include "301/CO_driver.h"
#include "cpufreq.h"
#include "log_message.h"
#include "board_info.h"
#include <dirent.h>
#include <errno.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

/** filepath remoteproc directory */
#define REMOTEPROC_DIR          "/sys/class/remoteproc/"

/** number of CPU(s) */
static uint8_t cpu_num = 0;
/** number of remote processors */
static uint8_t rproc_num = 0;
/** current remote processors */
static uint8_t rproc_cur = 0;
/** total ram memory */
static uint32_t ram_total = 0;
/** total swap memory */
static uint32_t swap_total = 0;
/** total root space */
static uint32_t root_total = 0;
/** hostname */
static char *hostname = NULL;
/** OS */
static char *os_name = NULL;
/** OS distro */
static char *os_distro = NULL;
/** kernel version */
static char *kernel_version = NULL;
/** CPU architecture */
static char *architecture = NULL;

// see function definition for doxygen comments
static int get_linux_distro_name(char *buf, int buf_len);
static int get_nremoteprocs(void);

int
board_info_setup(void) {
    struct utsname name;
    struct sysinfo info;
    struct statvfs fs_info;
    int buf_len = 256;
    char buf[buf_len];
    int len;

    CO_OD_configure(CO->SDO[0], OD_3001_boardInfo, board_info_ODF, NULL, 0, 0U);

    if(uname(&name) == 0) {
        // os name
        len = strlen(name.sysname)+1;
        os_name = (char *)malloc(len * sizeof(char));
        if(os_name != NULL)
            strncpy(os_name, name.sysname, len);
        else
            log_message(LOG_CRIT, "malloc failed for os_distro");

        // kernel version
        len = strlen(name.release)+1;
        kernel_version = (char *)malloc(len * sizeof(char));
        if(kernel_version != NULL)
            strncpy(kernel_version, name.release, len);
        else
            log_message(LOG_CRIT, "malloc failed for kernel_version");

        // hostname
        len = strlen(name.nodename)+1;
        hostname = (char *)malloc(len * sizeof(char));
        if(hostname != NULL)
            strncpy(hostname, name.nodename, len);
        else
            log_message(LOG_CRIT, "malloc failed for hostname");

        // architecture
        len = strlen(name.machine)+1;
        architecture = (char *)malloc(len * sizeof(char));
        if(architecture != NULL)
            strncpy(architecture, name.machine, len);
        else
            log_message(LOG_CRIT, "malloc failed for architecture");
    }

    // os distro name
    if (get_linux_distro_name(buf, buf_len) == 0) {
        len = strlen(buf)+1;
        os_distro = (char *)malloc(len * sizeof(char));
        strncpy(os_distro, buf, len);
    }

    if(sysinfo(&info) == 0) {
        swap_total = (uint32_t)(info.totalswap/1024/1024);
        ram_total = (uint32_t)(info.totalram/1024/1024);
    }

    if(statvfs("/", &fs_info) == 0)
        // the order help with int overflow on 32bit systems
        root_total = (uint32_t)(fs_info.f_blocks/1024*fs_info.f_bsize/1024);
    
    cpu_num = get_nprocs();
    rproc_num = get_nremoteprocs();
    
    return 0;
}

int
board_info_end(void) {
    if(os_distro != NULL)
        free(os_distro);

    if(kernel_version != NULL)
        free(kernel_version);

    if(hostname != NULL)
        free(hostname);

    if(architecture != NULL)
        free(architecture);

    if(os_name != NULL)
        free(os_name);

    return 0;
}

CO_SDO_abortCode_t
board_info_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    struct sysinfo info;
    struct statvfs fs_info;
    FILE *fptr = NULL; 
    int buf_len = 256;
    char filepath[PATH_MAX], buf[buf_len];
    uint8_t temp_uint8_t = 0;
    uint16_t temp_uint16_t = 0;
    uint32_t temp_uint32_t = 0;

    if(ODF_arg->reading == false && ODF_arg->subIndex != OD_3001_11_boardInfo_remoteprocXSelector)
        // every subindex is readonly except the remoteprocX selector subindex is readwrite
        return CO_SDO_AB_READONLY; 

    switch(ODF_arg->subIndex) {
        case OD_3001_1_boardInfo_OSName: // OS, domain, readonly
            ODF_arg->dataLength = strlen(os_name)+1;
            memcpy(ODF_arg->data, os_name, ODF_arg->dataLength);
            break;

        case OD_3001_2_boardInfo_OSDistro: // OS distro, domain, readonly
            ODF_arg->dataLength = strlen(os_distro)+1;
            memcpy(ODF_arg->data, os_distro, ODF_arg->dataLength);
            break;

        case OD_3001_3_boardInfo_OSKernelVersion: // kernel version, domain, readonly
            ODF_arg->dataLength = strlen(kernel_version)+1;
            memcpy(ODF_arg->data, kernel_version, ODF_arg->dataLength);
            break;

        case OD_3001_4_boardInfo_hostname: // hostname, domain, readonly
            ODF_arg->dataLength = strlen(hostname)+1;
            memcpy(ODF_arg->data, hostname, ODF_arg->dataLength);
            break;

        case OD_3001_5_boardInfo_uptime: // uptime (in min), uint32_t, readonly 
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.uptime/60);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_6_boardInfo_numberOfCPUs: // CPU(s), uint8_t, readonly
            ODF_arg->dataLength = sizeof(cpu_num);
            memcpy(ODF_arg->data, &cpu_num, ODF_arg->dataLength);
            break;

        case OD_3001_7_boardInfo_CPUArchitecture: // CPU Architecture, domain, readonly
            ODF_arg->dataLength = strlen(architecture)+1;
            memcpy(ODF_arg->data, architecture, ODF_arg->dataLength);
            break;

        case OD_3001_8_boardInfo_CPUGovernor: // CPU Governor, uint8_t, readonly
            temp_uint8_t = get_cpufreq_gov();
            ODF_arg->dataLength = sizeof(temp_uint8_t);
            memcpy(ODF_arg->data, &temp_uint8_t, ODF_arg->dataLength);
            break;

        case OD_3001_9_boardInfo_CPUFrequency: // CPU freq, uint16_t, readonly
            temp_uint16_t = get_cpufreq();
            ODF_arg->dataLength = sizeof(temp_uint16_t);
            memcpy(ODF_arg->data, &temp_uint16_t, ODF_arg->dataLength);
            break;

        case OD_3001_10_boardInfo_numberOfRemoteprocs: // Remoteproc(s), uint8_t, readonly
            ODF_arg->dataLength = sizeof(rproc_num);
            memcpy(ODF_arg->data, &rproc_num, ODF_arg->dataLength);
            break;

        case OD_3001_11_boardInfo_remoteprocXSelector: // RemoteprocX, uint8_t, readwrite
            if(ODF_arg->reading) {
                ODF_arg->dataLength = sizeof(rproc_cur);
                memcpy(ODF_arg->data, &rproc_cur, ODF_arg->dataLength);
            }
            else {
                memcpy(&temp_uint8_t, ODF_arg->data, ODF_arg->dataLength);
                if(temp_uint8_t < rproc_num)
                    rproc_cur = temp_uint8_t;
            }
            break;

        case OD_3001_12_boardInfo_remoteprocXName: // RemoteprocX name, domain, readonly
        sprintf(filepath, "%sremoteproc%d/name", REMOTEPROC_DIR, rproc_cur);
            if((fptr = fopen(filepath, "r")) != NULL) {
                fgets(buf, buf_len, fptr);
                fclose(fptr);
                buf[strlen(buf)-1] = '\0';
            }
            else // incase of file not exsiting
                buf[0] = '\0';

            ODF_arg->dataLength = strlen(buf)+1;
            memcpy(ODF_arg->data, buf, ODF_arg->dataLength);
            break;

        case OD_3001_13_boardInfo_remoteprocXState: // RemoteprocX state, uint8_t, readonly
            sprintf(filepath, "%sremoteproc%d/state", REMOTEPROC_DIR, rproc_cur);
            if((fptr = fopen(filepath, "r")) != NULL) {
                fgets(buf, buf_len, fptr);
                fclose(fptr);
                buf[strlen(buf)-1] = '\0';
            }
            else // incase of file not exsiting
                buf[0] = '\0';

            ODF_arg->dataLength = strlen(buf)+1;
            memcpy(ODF_arg->data, buf, ODF_arg->dataLength);
            break;

        case OD_3001_14_boardInfo_loadAverage1min: // 1min load avg, uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)info.loads[0];

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_15_boardInfo_loadAverage5min: // 5min load avg, uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)info.loads[1];

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_16_boardInfo_loadAverage15min: // 15min load avg, uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)info.loads[2];

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_17_boardInfo_ramTotal: // Free ram (in MiB), uint32_t, readonly
            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &ram_total, ODF_arg->dataLength);
            break;

        case OD_3001_18_boardInfo_ramFree: // Free ram (in MiB), uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.freeram/1024/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_19_boardInfo_ramShared: // Shared ram (in MiB), uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.sharedram/1024/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_20_boardInfo_ramBuffered: // Buffer ram (in MiB), uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.bufferram/1024/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_21_boardInfo_ramPercent: // Ram usage percent (0-100%), uint8_t, readonly
            if(sysinfo(&info) != -1) 
                temp_uint8_t = (uint8_t)((info.totalram - info.freehigh) / info.totalram);

            ODF_arg->dataLength = sizeof(temp_uint8_t);
            memcpy(ODF_arg->data, &temp_uint8_t, ODF_arg->dataLength);
            break;

        case OD_3001_22_boardInfo_swapTotal: // Total swap (in MiB), uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.totalswap/1024/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_23_boardInfo_swapFree: // Free swap (in MiB), uint32_t, readonly
            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &swap_total, ODF_arg->dataLength);
            break;

        case OD_3001_24_boardInfo_swapPercent: // Swap usage percent (0-100%), uint8_t, readonly
            if(sysinfo(&info) != -1) 
                temp_uint8_t = (uint8_t)((info.totalswap - info.freeswap) / info.totalswap);

            ODF_arg->dataLength = sizeof(temp_uint8_t);
            memcpy(ODF_arg->data, &temp_uint8_t, ODF_arg->dataLength);
            break;

        case OD_3001_25_boardInfo_procs: // Number of procs, uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)info.procs;

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_26_boardInfo_rootParitionTotal: // Root partion total (in MiB), uint32_t, readonly
            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &root_total, ODF_arg->dataLength);
            break;

        case OD_3001_27_boardInfo_rootParitionFree: // Root partion free (in MiB), uint32_t, readonly
            if((statvfs("/", &fs_info)) == 0 )
                // the order help with int overflow on 32bit systems
                temp_uint32_t = (uint32_t)(fs_info.f_bavail/1024*fs_info.f_bsize/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case OD_3001_28_boardInfo_rootParitionPercent: // Root partion usage percent (0-100%), uint8_t, readonly
            if((statvfs("/", &fs_info)) == 0 )
                temp_uint8_t = (uint8_t)((fs_info.f_blocks - fs_info.f_bavail) / fs_info.f_blocks);

            ODF_arg->dataLength = sizeof(temp_uint8_t);
            memcpy(ODF_arg->data, &temp_uint8_t, ODF_arg->dataLength);
            break;
    }

    return ret;
}

static int
get_linux_distro_name(char *buf, int buf_len) {
    FILE* filePointer;
    bool found = false;
    char *temp  = NULL;

    if((filePointer = fopen("/etc/os-release", "r")) == NULL)
        return -ENOENT;
   
    while(fgets(buf, buf_len, filePointer)) {
        if(strncmp(buf, "PRETTY_NAME", strlen("PRETTY_NAME")) == 0) {
            found = true;
            break;
        }
    }
    
    fclose(filePointer);

    if(found != true) {
        buf[0] = '\0';
    }
    else { 
        temp = strrchr(buf, '\"');
        *temp = '\0';
        temp = strchr(buf, '\"');
        strncpy(buf, &temp[1], strlen(temp)+1);
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
    if(stat(REMOTEPROC_DIR, &st) == -1) {
        return nremoteproc;
    }
    
    if((d = opendir(REMOTEPROC_DIR)) != NULL) { // add all existing file to list
        while((dir = readdir(d)) != NULL) { // directory found
            if(strncmp(dir->d_name, ".", sizeof(dir->d_name)) == 0 ||
                    strncmp(dir->d_name, "..", sizeof(dir->d_name)) == 0)
                continue; // skip . and ..

            ++nremoteproc;
        }
        closedir(d);
    }

    return nremoteproc;
}

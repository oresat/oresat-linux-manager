/**
 * Board Info Object Dictionary Function.
 *
 * @file        board_info.c
 * @ingroup     board_info
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */

#include "CANopen.h"
#include "CO_driver.h"
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

#ifndef BI_I
/** Board Info ODF index */
#define BI_I                    0x3000
#endif

/* Board info subindices */
#define BI_SI_OS                1
#define BI_SI_OS_DISTRO         BI_SI_OS+1
#define BI_SI_OS_KERNEL         BI_SI_OS_DISTRO+1
#define BI_SI_HOSTNAME          BI_SI_OS_KERNEL+1
#define BI_SI_UPTIME            BI_SI_HOSTNAME+1
#define BI_SI_CPUS              BI_SI_UPTIME+1
#define BI_SI_CPU_ARCH          BI_SI_CPUS+1
#define BI_SI_CPU_GOV           BI_SI_CPU_ARCH+1
#define BI_SI_CPU_FREQ          BI_SI_CPU_GOV+1
#define BI_SI_RPROCS            BI_SI_CPU_FREQ+1
#define BI_SI_RPROCS_X          BI_SI_RPROCS+1
#define BI_SI_RPROCS_X_NAME     BI_SI_RPROCS_X+1
#define BI_SI_RPROCS_X_STATE    BI_SI_RPROCS_X_NAME+1
#define BI_SI_1MIN_LOAD_AVG     BI_SI_RPROCS_X_STATE+1
#define BI_SI_5MIN_LOAD_AVG     BI_SI_1MIN_LOAD_AVG+1
#define BI_SI_15MIN_LOAD_AVG    BI_SI_5MIN_LOAD_AVG+1
#define BI_SI_FREE_RAM          BI_SI_15MIN_LOAD_AVG+1
#define BI_SI_SHARED_RAM        BI_SI_FREE_RAM+1
#define BI_SI_BUFFER_RAM        BI_SI_SHARED_RAM+1
#define BI_SI_TOTAL_SWAP        BI_SI_BUFFER_RAM+1
#define BI_SI_FREE_SWAP         BI_SI_TOTAL_SWAP+1
#define BI_SI_PROCS             BI_SI_FREE_SWAP+1
#define BI_SI_ROOT_TOTAL        BI_SI_PROCS+1
#define BI_SI_ROOT_FREE         BI_SI_ROOT_TOTAL+1
#define BI_SI                   BI_SI_ROOT_FREE+1 // must be last

/** filepath remoteproc directory */
#define REMOTEPROC_DIR          "/sys/class/remoteproc/"


/** number of CPU(s) */
static uint8_t cpu_num = 0;
/** number of remote processors */
static uint8_t rproc_num = 0;
/** current remote processors */
static uint8_t rproc_cur = 0;
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

    CO_OD_configure(CO->SDO[0], BI_I, board_info_ODF, NULL, 0, 0U);

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

    if(sysinfo(&info) == 0)
        swap_total = (uint32_t)(info.totalswap/1024/1024);

    if(statvfs("/", &fs_info) == 0)
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
    uint8_t subindices = BI_SI;
    uint8_t temp_uint8_t = 0;
    uint16_t temp_uint16_t = 0;
    uint32_t temp_uint32_t = 0;

    if(ODF_arg->reading == false && ODF_arg->subIndex != BI_SI_RPROCS_X)
        // everything is readonly except BI_SI_RPROCS_X is readwrite
        return CO_SDO_AB_READONLY; 

    switch(ODF_arg->subIndex) {
        case 0: // number of subindexes, uint8_t, readonly
            ODF_arg->dataLength = sizeof(subindices);
            memcpy(ODF_arg->data, &subindices, ODF_arg->dataLength);
            break;

        case BI_SI_OS: // OS, domain, readonly
            ODF_arg->dataLength = strlen(os_name)+1;
            memcpy(ODF_arg->data, os_name, ODF_arg->dataLength);
            break;

        case BI_SI_OS_DISTRO: // OS distro, domain, readonly
            ODF_arg->dataLength = strlen(os_distro)+1;
            memcpy(ODF_arg->data, os_distro, ODF_arg->dataLength);
            break;

        case BI_SI_OS_KERNEL: // kernel version, domain, readonly
            ODF_arg->dataLength = strlen(kernel_version)+1;
            memcpy(ODF_arg->data, kernel_version, ODF_arg->dataLength);
            break;

        case BI_SI_HOSTNAME: // hostname, domain, readonly
            ODF_arg->dataLength = strlen(hostname)+1;
            memcpy(ODF_arg->data, hostname, ODF_arg->dataLength);
            break;

        case BI_SI_UPTIME: // uptime (in min), uint32_t, readonly 
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.uptime/60);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_CPUS: // CPU(s), uint8_t, readonly
            ODF_arg->dataLength = sizeof(cpu_num);
            memcpy(ODF_arg->data, &cpu_num, ODF_arg->dataLength);
            break;

        case BI_SI_CPU_ARCH: // CPU Architecture, domain, readonly
            ODF_arg->dataLength = strlen(architecture)+1;
            memcpy(ODF_arg->data, architecture, ODF_arg->dataLength);
            break;

        case BI_SI_CPU_GOV: // CPU Governor, uint8_t, readonly
            temp_uint8_t = get_cpufreq_gov();
            ODF_arg->dataLength = sizeof(temp_uint8_t);
            memcpy(ODF_arg->data, &temp_uint8_t, ODF_arg->dataLength);
            break;

        case BI_SI_CPU_FREQ: // CPU freq, uint16_t, readonly
            temp_uint16_t = get_cpufreq();
            ODF_arg->dataLength = sizeof(temp_uint16_t);
            memcpy(ODF_arg->data, &temp_uint16_t, ODF_arg->dataLength);
            break;

        case BI_SI_RPROCS: // Remoteproc(s), uint8_t, readonly
            ODF_arg->dataLength = sizeof(rproc_num);
            memcpy(ODF_arg->data, &rproc_num, ODF_arg->dataLength);
            break;

        case BI_SI_RPROCS_X: // RemoteprocX, uint8_t, readwrite
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

        case BI_SI_RPROCS_X_NAME: // RemoteprocX name, domain, readonly
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

        case BI_SI_RPROCS_X_STATE: // RemoteprocX state, uint8_t, readonly
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

        case BI_SI_1MIN_LOAD_AVG: // 1min load avg, uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)info.loads[0];

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_5MIN_LOAD_AVG: // 5min load avg, uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)info.loads[1];

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_15MIN_LOAD_AVG: // 15min load avg, uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)info.loads[2];

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_FREE_RAM: // Free ram (in MiB), uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.freeram/1024/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_SHARED_RAM: // Shared ram (in MiB), uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.sharedram/1024/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_BUFFER_RAM: // Buffer ram (in MiB), uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.bufferram/1024/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_TOTAL_SWAP: // Total swap (in MiB), uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.totalswap/1024/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_FREE_SWAP: // Free swap (in MiB), uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)(info.freeswap/1024/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_PROCS: // Number of procs, uint32_t, readonly
            if(sysinfo(&info) != -1)
                temp_uint32_t = (uint32_t)info.procs;

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_ROOT_TOTAL: // Root partion total (in MiB), uint32_t, readonly
            if((statvfs("/", &fs_info)) == 0 )
                // the order help with int overflow on 32bit systems
                temp_uint32_t = (uint32_t)(fs_info.f_blocks/1024*fs_info.f_bsize/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        case BI_SI_ROOT_FREE: // Root partion free (in MiB), uint32_t, readonly
            if((statvfs("/", &fs_info)) == 0 )
                // the order help with int overflow on 32bit systems
                temp_uint32_t = (uint32_t)(fs_info.f_bavail/1024*fs_info.f_bsize/1024);

            ODF_arg->dataLength = sizeof(temp_uint32_t);
            memcpy(ODF_arg->data, &temp_uint32_t, ODF_arg->dataLength);
            break;

        default:
            ret = CO_SDO_AB_SUB_UNKNOWN;

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

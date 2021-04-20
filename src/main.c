#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <signal.h>
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>
#include <time.h>
#include <sys/epoll.h>
#include <net/if.h>
#include <linux/reboot.h>
#include <sys/reboot.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <systemd/sd-bus.h>

#include "CANopen.h"
#include "boards/generic/object_dictionary/CO_OD.h"
#include "logging.h"
#include "CO_error.h"
#include "CO_epoll_interface.h"

#include "configs.h"
#include "utility.h"
#include "CO_fstream_odf.h"
#include "file_caches_odf.h"
#include "systemd.h"
#include "olm_app.h"
#include "system_info.h"
#include "board_main.h"
#include "os_command.h"
#include "olm_control_odf.h"
#include "app_manager.h"
#include "olm_file_cache.h"
#include "CO_fstream_odf.h"
#include "file_caches_odf.h"
#include "ecss_time.h"
#if TIME_PRODUCER
#include "time_producer.h"
#else
#include "time_sync.h"
#endif

/* Interval of mainline and real-time thread in microseconds */
#ifndef MAIN_THREAD_INTERVAL_US
#define MAIN_THREAD_INTERVAL_US 100000
#endif
#ifndef TMR_THREAD_INTERVAL_US
#define TMR_THREAD_INTERVAL_US  1000
#endif

#define ASYNC_DELAY             100000

// pid file for daemon
#define DEFAULT_PID_FILE        "/run/oresat-linux-managerd.pid"

#ifndef FILE_TRANSFER_DIR
#define FILE_TRANSFER_DIR       "/var/cache/oresat_linux_manager/"
#endif /* FILE_TRANSFER_DIR */

#ifndef FREAD_TMP_DIR
#define FREAD_TMP_DIR           FILE_TRANSFER_DIR"CANopen/fread/"
#endif /* FREAD_TMP_DIR */

#ifndef FWRITE_TMP_DIR
#define FWRITE_TMP_DIR          FILE_TRANSFER_DIR"CANopen/fwrite/"
#endif /* FWRITE_TMP_DIR */

#ifndef FREAD_CACHE_DIR
#define FREAD_CACHE_DIR         FILE_TRANSFER_DIR"fread/"
#endif /* FREAD_CACHE_DIR */

#ifndef FWRITE_CACHE_DIR
#define FWRITE_CACHE_DIR        FILE_TRANSFER_DIR"fwrite/"
#endif /* FWRITE_CACHE_DIR */

#define DBUS_TIMEOUT_US         100000

static uint8_t CO_activeNodeId = NODE_ID_DEFAULT;

#if (CO_CONFIG_TRACE) & CO_CONFIG_TRACE_ENABLE
static CO_time_t            CO_time;            /* Object for current time */
#endif

/* OLM globals  **************************************************************/
static olm_configs_t configs = OLM_CONFIGS_DEFAULT;
static os_command_t os_command_data;
static olm_file_cache_t *fread_cache = NULL;
static olm_file_cache_t *fwrite_cache = NULL;
static system_info_t system_info = SYSTEM_INFO_DEFAULT;

// not static
sd_bus *core_bus = NULL;
sd_bus *apps_bus = NULL;

/* Helper functions **********************************************************/
/* Realtime thread */
CO_epoll_t epRT;
static void* rt_thread(void* arg);

/* oresat linux manager app thread */
static void* app_thread(void* arg);
static pthread_t app_thread_id;

/* async thread */
static void* async_thread(void* arg);
static pthread_t async_thread_id;

/* make daemon */
int make_daemon(const char *pid_file);

/* Signal handler */
volatile sig_atomic_t CO_endProgram = 0;
static void sigHandler(int sig) {
    (void)sig;
    CO_endProgram = 1;
}

#if (CO_CONFIG_EM) & CO_CONFIG_EM_CONSUMER
/* callback for emergency messages */
static void EmergencyRxCallback(const uint16_t ident,
                                const uint16_t errorCode,
                                const uint8_t errorRegister,
                                const uint8_t errorBit,
                                const uint32_t infoCode)
{
    int16_t nodeIdRx = ident ? (ident&0x7F) : CO_activeNodeId;

    log_printf(LOG_NOTICE, DBG_EMERGENCY_RX, nodeIdRx, errorCode,
               errorRegister, errorBit, infoCode);
}
#endif

#if ((CO_CONFIG_NMT) & CO_CONFIG_NMT_CALLBACK_CHANGE) \
 || ((CO_CONFIG_HB_CONS) & CO_CONFIG_HB_CONS_CALLBACK_CHANGE)
/* return string description of NMT state. */
static char *NmtState2Str(CO_NMT_internalState_t state)
{
    switch(state) {
        case CO_NMT_INITIALIZING:    return "initializing";
        case CO_NMT_PRE_OPERATIONAL: return "pre-operational";
        case CO_NMT_OPERATIONAL:     return "operational";
        case CO_NMT_STOPPED:         return "stopped";
        default:                     return "unknown";
    }
}
#endif

#if (CO_CONFIG_NMT) & CO_CONFIG_NMT_CALLBACK_CHANGE
/* callback for NMT change messages */
static void NmtChangedCallback(CO_NMT_internalState_t state)
{
    log_printf(LOG_NOTICE, DBG_NMT_CHANGE, NmtState2Str(state), state);
}
#endif

#if (CO_CONFIG_HB_CONS) & CO_CONFIG_HB_CONS_CALLBACK_CHANGE
/* callback for monitoring Heartbeat remote NMT state change */
static void HeartbeatNmtChangedCallback(uint8_t nodeId, uint8_t idx,
                                        CO_NMT_internalState_t state,
                                        void *object)
{
    (void)object;
    log_printf(LOG_NOTICE, DBG_HB_CONS_NMT_CHANGE,
               nodeId, idx, NmtState2Str(state), state);
}
#endif

/* Print usage */
static void printUsage(char *progName) {
printf(
"Usage: %s [options]\n", progName);
printf(
"\n"
"Options:\n");
printf(
"  -h                   Print this message and exit.\n");
printf(
"  -i <Interface>       CANbus interface (can0, vcan0, etc).\n");
printf(
"  -n <Node ID>         CANopen Node-id (1..127).\n");
printf(
"  -p <RT priority>     Real-time priority of RT thread (1 .. 99). If not set or\n"
"                       set to -1, then normal scheduler is used for RT thread.\n");
printf(
"  -r                   Enable reboot on CANopen NMT reset_node command. \n");
printf(
"  -d                   Run the process as a daemon.\n");
printf(
"  -v                   Enable verbose logging.\n");
printf(
"  -c                   Enable CPU frequency control.\n");
}


/*******************************************************************************
 * Mainline thread
 ******************************************************************************/
int
main(int argc, char *argv[]) {
    int programExit = EXIT_SUCCESS;
    CO_epoll_t epMain;
    pthread_t rt_thread_id;
    int rtPriority = -1;
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;
    CO_ReturnError_t err;
    CO_CANptrSocketCan_t CANptr = {0};
    int opt;
    bool firstRun = true;
    bool daemon_flag = false;
    bool verbose = false;
    bool cpufreq_ctrl = false;
    bool rebootEnable = false;

    /* Read conf file */
    read_config_file(&configs);
    
    /* Get program options */
    while ((opt = getopt(argc, argv, "hi:n:p:rdvc")) != -1) {
        switch (opt) {
            case 'h':
                printUsage(argv[0]);
                exit(EXIT_SUCCESS);
            case 'i':
                strncpy(configs.interface, optarg, strlen(optarg)+1);
                break;
            case 'n':
                configs.node_id = (uint8_t)strtol(optarg, NULL, 0);
                break;
            case 'p':
                rtPriority = strtol(optarg, NULL, 0);
                break;
            case 'r':
                rebootEnable = true;
                break;
            case 'd':
                daemon_flag = true;
                break;
            case 'v':
                verbose = true;
                break;
            case 'c':
                cpufreq_ctrl = true;
                break;
            default:
                printUsage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (verbose)
        setlogmask(LOG_UPTO (LOG_DEBUG)); /* log all messages */
    else
        setlogmask(LOG_UPTO (LOG_INFO)); 

    if (!daemon_flag)
        openlog(argv[0], LOG_PID | LOG_PERROR, LOG_USER); /* print also to standard error */

    CANptr.can_ifindex = if_nametoindex(configs.interface);

    if (configs.node_id < 1 || configs.node_id > 127) {
        log_printf(LOG_CRIT, DBG_WRONG_NODE_ID, configs.node_id);
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (rtPriority != -1 && (rtPriority < sched_get_priority_min(SCHED_FIFO)
                         || rtPriority > sched_get_priority_max(SCHED_FIFO))) {
        log_printf(LOG_CRIT, DBG_WRONG_PRIORITY, rtPriority);
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (CANptr.can_ifindex == 0) {
        log_printf(LOG_CRIT, DBG_NO_CAN_DEVICE, configs.interface);
        exit(EXIT_FAILURE);
    }

    // make all the dirs
    if (mkdir_path(FREAD_CACHE_DIR, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH |  S_IXOTH) != 0)
        log_printf(LOG_CRIT, "failed to make fread cache dir "FREAD_CACHE_DIR);
    if (mkdir_path(FWRITE_CACHE_DIR, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0)
        log_printf(LOG_CRIT, "failed to make fwrite cache dir "FWRITE_CACHE_DIR);
    if (mkdir_path(FREAD_TMP_DIR, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0)
        log_printf(LOG_CRIT, "failed to make fread tmp dir "FREAD_TMP_DIR);
    if (mkdir_path(FWRITE_TMP_DIR, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0)
        log_printf(LOG_CRIT, "failed to make fwrite tmp dir "FWRITE_TMP_DIR);

    // clean up any file in the tmp dirs
    clear_dir(FREAD_TMP_DIR);
    clear_dir(FWRITE_TMP_DIR);

    // file transfer data
    olm_file_cache_new(FREAD_CACHE_DIR, &fread_cache);
    olm_file_cache_new(FWRITE_CACHE_DIR, &fwrite_cache);
    CO_fstream_t CO_fread_data = CO_FSTREAM_INITALIZER(FREAD_TMP_DIR, fread_cache);
    CO_fstream_t CO_fwrite_data = CO_FSTREAM_INITALIZER(FWRITE_TMP_DIR, fwrite_cache);
    file_caches_t caches_odf_data = FILE_CACHES_INTIALIZER(fread_cache, fwrite_cache);

    /* Run as daemon if needed */
    if (daemon_flag) {
        log_printf(LOG_INFO, "daemonizing process");
        make_daemon(DEFAULT_PID_FILE);
    }

    // change the TPDO COB-ID, no needed for lock as nothing else exist yet.
    for (int i=0; i< CO_NO_TPDO; ++i)
        OD_TPDOCommunicationParameter[i].COB_IDUsedByTPDO += configs.node_id;

    log_printf(LOG_INFO, DBG_CAN_OPEN_INFO, configs.node_id, "starting");

    if (sd_bus_open_system(&core_bus) < 0)
        log_printf(LOG_CRIT, "open system bus for OLM core failed");
    if (sd_bus_open_system(&apps_bus) < 0)
        log_printf(LOG_CRIT, "open system bus for apps failed");

    // set method and therefor priorities to timeout after 1 second.
    // otherwise it defaults to 25 seconds
    sd_bus_set_method_call_timeout(core_bus, 1000000);
    sd_bus_set_method_call_timeout(apps_bus, 1000000);

    /* Allocate memory for CANopen objects */
    err = CO_new(NULL);
    if (err != CO_ERROR_NO) {
        log_printf(LOG_CRIT, DBG_CAN_OPEN, "CO_new()", err);
        exit(EXIT_FAILURE);
    }

    /* Catch signals SIGINT and SIGTERM */
    if (signal(SIGINT, sigHandler) == SIG_ERR) {
        log_printf(LOG_CRIT, DBG_ERRNO, "signal(SIGINT, sigHandler)");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGTERM, sigHandler) == SIG_ERR) {
        log_printf(LOG_CRIT, DBG_ERRNO, "signal(SIGTERM, sigHandler)");
        exit(EXIT_FAILURE);
    }

    /* Create epoll functions */
    err = CO_epoll_create(&epMain, MAIN_THREAD_INTERVAL_US);
    if (err != CO_ERROR_NO) {
        log_printf(LOG_CRIT, DBG_GENERAL,
                   "CO_epoll_create(main), err=", err);
        exit(EXIT_FAILURE);
    }

    err = CO_epoll_create(&epRT, TMR_THREAD_INTERVAL_US);
    if (err != CO_ERROR_NO) {
        log_printf(LOG_CRIT, DBG_GENERAL,
                   "CO_epoll_create(RT), err=", err);
        exit(EXIT_FAILURE);
    }
    CANptr.epoll_fd = epRT.epoll_fd;
    
    if (cpufreq_ctrl) {
        CO_LOCK_OD();
        OD_OLMControl.CPUFrequency = true;
        CO_UNLOCK_OD();
    }

    while (reset != CO_RESET_APP && reset != CO_RESET_QUIT && CO_endProgram == 0) {
/* CANopen communication reset - initialize CANopen objects *******************/

        if (OD_OLMControl.quit) {
            CO_endProgram = true;
            continue;
        }

        /* Wait rt_thread. */
        if (!firstRun) {
            CO_LOCK_OD();
            CO->CANmodule[0]->CANnormal = false;
            CO_UNLOCK_OD();
        }

        /* Enter CAN configuration. */
        CO_CANsetConfigurationMode((void *)&CANptr);
        CO_CANmodule_disable(CO->CANmodule[0]);


        /* initialize CANopen */
        err = CO_CANinit((void *)&CANptr, 0 /* bit rate not used */);
        if (err != CO_ERROR_NO) {
            log_printf(LOG_CRIT, DBG_CAN_OPEN, "CO_CANinit()", err);
            programExit = EXIT_FAILURE;
            CO_endProgram = 1;
            continue;
        }

        CO_activeNodeId = configs.node_id;

        err = CO_CANopenInit(CO_activeNodeId);
        if (err != CO_ERROR_NO && err != CO_ERROR_NODE_ID_UNCONFIGURED_LSS) {
            log_printf(LOG_CRIT, DBG_CAN_OPEN, "CO_CANopenInit()", err);
            programExit = EXIT_FAILURE;
            CO_endProgram = 1;
            continue;
        }

        /* initialize part of threadMain and callbacks */
        CO_epoll_initCANopenMain(&epMain, CO);

        if (!CO->nodeIdUnconfigured) {
#if (CO_CONFIG_EM) & CO_CONFIG_EM_CONSUMER
            CO_EM_initCallbackRx(CO->em, EmergencyRxCallback);
#endif
#if (CO_CONFIG_NMT) & CO_CONFIG_NMT_CALLBACK_CHANGE
            CO_NMT_initCallbackChanged(CO->NMT, NmtChangedCallback);
#endif
#if (CO_CONFIG_HB_CONS) & CO_CONFIG_HB_CONS_CALLBACK_CHANGE
            CO_HBconsumer_initCallbackNmtChanged(CO->HBcons, NULL,
                                                 HeartbeatNmtChangedCallback);
#endif

#if (CO_CONFIG_TRACE) & CO_CONFIG_TRACE_ENABLE
            /* Initialize time */
            CO_time_init(&CO_time, CO->SDO[0], &OD_time.epochTimeBaseMs, &OD_time.epochTimeOffsetMs, 0x2130);
#endif

            if (app_manager_init(APPS) < 0)
                log_printf(LOG_ERR, "app_manager_init() failed");
            
            // configure core ODFs
            board_init();
            CO_OD_configure(CO->SDO[0], OD_1023_OSCommand, OS_COMMAND_1023_ODF, &os_command_data, 0, 0U);
            CO_OD_configure(CO->SDO[0], OD_3000_OLMControl, olm_control_ODF, NULL, 0, 0U);
            CO_OD_configure(CO->SDO[0], OD_3001_systemInfo, system_info_ODF, &system_info, 0, 0U);
            CO_OD_configure(CO->SDO[0], OD_3002_fileCaches, file_caches_ODF, &caches_odf_data, 0, 0U);
            CO_OD_configure(CO->SDO[0], OD_3003_fread, CO_fread_ODF, &CO_fread_data, 0, 0U);
            CO_OD_configure(CO->SDO[0], OD_3004_fwrite, CO_fwrite_ODF, &CO_fwrite_data, 0, 0U);
            CO_OD_configure(CO->SDO[0], OD_3005_appManager, app_manager_ODF, APPS, 0, 0U);
#if TIME_PRODUCER
            CO_OD_configure(CO->SDO[0], OD_2010_SCET, time_producer_ODF, NULL, 0, 0U);
#else
            CO_OD_configure(CO->SDO[0], OD_2010_SCET, SCET_ODF, NULL, 0, 0U);
#endif

            log_printf(LOG_INFO, DBG_CAN_OPEN_INFO, CO_activeNodeId, "communication reset");
        }
        else {
            log_printf(LOG_INFO, DBG_CAN_OPEN_INFO, CO_activeNodeId, "node-id not initialized");
        }

        /* First time only initialization. */
        if (firstRun) {
            firstRun = false;

            /* Create rt_thread and set priority */
            if (pthread_create(&rt_thread_id, NULL, rt_thread, NULL) != 0) {
                log_printf(LOG_CRIT, DBG_ERRNO, "pthread_create(rt_thread)");
                programExit = EXIT_FAILURE;
                CO_endProgram = 1;
                continue;
            }
            if (rtPriority > 0) {
                struct sched_param param;

                param.sched_priority = rtPriority;
                if (pthread_setschedparam(rt_thread_id, SCHED_FIFO, &param) != 0) {
                    log_printf(LOG_CRIT, DBG_ERRNO, "pthread_setschedparam()");
                    programExit = EXIT_FAILURE;
                    CO_endProgram = 1;
                    continue;
                }
            }

            /* create async thread */
            if(pthread_create(&async_thread_id, NULL, async_thread, NULL) != 0) {
                log_printf(LOG_CRIT, DBG_ERRNO, "pthread_create(async_thread)");
                exit(EXIT_FAILURE);
            }

            /* create app thread */
            if(pthread_create(&app_thread_id, NULL, app_thread, NULL) != 0) {
                log_printf(LOG_CRIT, DBG_ERRNO, "pthread_create(app_thread)");
                exit(EXIT_FAILURE);
            }
        } /* if (firstRun) */

        /* Execute optional additional application code */
        // TODO app comm reset

        /* start CAN */
        CO_CANsetNormalMode(CO->CANmodule[0]);

        reset = CO_RESET_NOT;

        log_printf(LOG_INFO, DBG_CAN_OPEN_INFO, CO_activeNodeId, "running ...");

        while (reset == CO_RESET_NOT && CO_endProgram == 0) {
/* loop for normal program execution ******************************************/
            CO_epoll_wait(&epMain);
            CO_epoll_processRT(&epMain, CO, false);
            CO_epoll_processMain(&epMain, CO, &reset);
            CO_epoll_processLast(&epMain);
        }

        log_printf(LOG_DEBUG, "CO reset or end program signal");
    } /* while (reset != CO_RESET_APP */

    log_printf(LOG_DEBUG, "ending program");

/* program exit ***************************************************************/
    system_info_free(&system_info);

    // make sure the files are closed when ending program
    log_printf(LOG_DEBUG, "closing any opened files");
    CO_fstream_reset(&CO_fread_data);
    CO_fstream_reset(&CO_fwrite_data);

    log_printf(LOG_DEBUG, "cleaning cache data");
    file_caches_free(&caches_odf_data);
    olm_file_cache_free(fread_cache);
    olm_file_cache_free(fwrite_cache);

    if (!firstRun) {
        log_printf(LOG_DEBUG, "joining threads");
        CO_endProgram = 1;

        if (pthread_join(rt_thread_id, NULL) != 0)
            log_printf(LOG_CRIT, DBG_ERRNO, "pthread_join()");
        if (pthread_join(async_thread_id, NULL) != 0)
            log_printf(LOG_CRIT, DBG_ERRNO, "pthread_join()");
        if (pthread_join(app_thread_id, NULL) != 0)
            log_printf(LOG_CRIT, DBG_ERRNO, "pthread_join()");
    }

    if (core_bus != NULL)
        sd_bus_unref(core_bus);
    if (apps_bus != NULL)
        sd_bus_unref(apps_bus);

    /* delete objects from memory */
    CO_epoll_close(&epRT);
    CO_epoll_close(&epMain);
    CO_CANsetConfigurationMode((void *)&CANptr);
    CO_delete((void *)&CANptr);

    log_printf(LOG_INFO, DBG_CAN_OPEN_INFO, CO_activeNodeId, "finished");

    if (daemon_flag)
        remove(DEFAULT_PID_FILE);

    /* Flush all buffers (and reboot) */
    if (rebootEnable && reset == CO_RESET_APP) {
        sync();
        if (reboot(LINUX_REBOOT_CMD_RESTART) != 0) {
            log_printf(LOG_CRIT, DBG_ERRNO, "reboot()");
            exit(EXIT_FAILURE);
        }
    }

    exit(programExit);
}

/*******************************************************************************
 * Realtime thread for CAN receive and threadTmr
 ******************************************************************************/
static void* rt_thread(void* arg) {
    (void)arg;
    log_printf(LOG_DEBUG, "rt thread started");

    /* Endless loop */
    while (CO_endProgram == 0) {

        CO_epoll_wait(&epRT);
        CO_epoll_processRT(&epRT, CO, true);
        CO_epoll_processLast(&epRT);

#if (CO_CONFIG_TRACE) & CO_CONFIG_TRACE_ENABLE
        /* Monitor variables with trace objects */
        CO_time_process(&CO_time);
        for (i=0; i<OD_traceEnable && i<CO_NO_TRACE; i++) {
            CO_trace_process(CO->trace[i], *CO_time.epochTimeOffsetMs);
        }
#endif
    }

    log_printf(LOG_DEBUG, "rt thread ended");
    return NULL;
}

static void*
app_thread(void* arg) {
    (void)arg;
    log_printf(LOG_DEBUG, "app thread started");

    /* Endless loop */
    while (CO_endProgram == 0) {
        for (int i=0; APPS[i] != NULL; ++i) {
            if (APPS[i]->async_cb != NULL && APPS[i]->unit_state == UNIT_ACTIVE)
                APPS[i]->async_cb(APPS[i]->data, fread_cache);
        }

        usleep(ASYNC_DELAY);
    }

    log_printf(LOG_DEBUG, "app thread ended");
    return NULL;
}

static void*
async_thread(void* arg) {
    (void)arg;
    log_printf(LOG_DEBUG, "async thread started");

    /* Endless loop */
    while (CO_endProgram == 0) {
        system_info_async(&system_info);
        co_command_async(&os_command_data);
        app_manager_async(APPS, fwrite_cache);
        usleep(ASYNC_DELAY);
    }

    log_printf(LOG_DEBUG, "async thread ended");
    return NULL;
}

int
make_daemon(const char *pid_file) {
    FILE *run_fp = NULL;
    pid_t pid = 0, sid = 0;

    log_printf(LOG_DEBUG, "Starting as daemon...\n");
    /* Fork */
    if ((pid = fork()) < 0) {
        log_printf(LOG_ERR, "Error: Failed to fork!\n");
        exit(EXIT_FAILURE);
    }

    /* Parent process exits */
    if (pid) {
        exit(EXIT_SUCCESS);
    }

    /* Child process continues on */
    /* Log PID */
    if ((run_fp = fopen(pid_file, "w+")) == NULL) {
        log_printf(LOG_ERR, "Error: Unable to open file %s\n", pid_file);
        exit(EXIT_FAILURE);
    }
    fprintf(run_fp, "%d\n", getpid());
    fflush(run_fp);
    fclose(run_fp);

    /* Create new session for process group leader */
    if ((sid = setsid()) < 0) {
        log_printf(LOG_ERR, "Error: Failed to create new session!\n");
        exit(EXIT_FAILURE);
    }

    /* Set default umask and cd to root to avoid blocking filesystems */
    umask(0);
    if (chdir("/") < 0) {
        log_printf(LOG_ERR, "Error: Failed to chdir to root: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Redirect std streams to /dev/null */
    if (freopen("/dev/null", "r", stdin) == NULL) {
        log_printf(LOG_ERR, "Error: Failed to redirect streams to /dev/null!\n");
        exit(EXIT_FAILURE);
    }
    if (freopen("/dev/null", "w+", stdout) == NULL) {
        log_printf(LOG_ERR, "Error: Failed to redirect streams to /dev/null!\n");
        exit(EXIT_FAILURE);
    }
    if (freopen("/dev/null", "w+", stderr) == NULL) {
        log_printf(LOG_ERR, "Error: Failed to redirect streams to /dev/null!\n");
        exit(EXIT_FAILURE);
    }

    return 1;
}

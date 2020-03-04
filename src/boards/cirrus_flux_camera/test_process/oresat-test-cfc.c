#include "testprucam.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <systemd/sd-bus.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <syslog.h>
#include <stdarg.h>


#define TMR_TASK_INTERVAL_NS    (1000000)       // Interval of taskTmr in nanoseconds
#define TMR_TASK_OVERFLOW_US    (5000)          // Overflow detect limit for taskTmr in microseconds


#define DESTINATION         "org.OreSat.CirrusFluxCamera"
#define BUS_NAME            "org.OreSat.CirrusFluxCamera"
#define OBJECT_PATH         "/org/OreSat/CirrusFluxCamera"
#define DEFAULT_PID_FILE    "/run/oresat-test-cfc.pid"


/* static data */
static const sd_bus_vtable method_vtable[];
static sd_bus_slot *slot = NULL;
static sd_bus *bus = NULL;
static bool endProgram = 0;
static char file_path[200];


/* static functions */
static int lastest_image(sd_bus_message *m, void *systemdata, sd_bus_error *ret_error);
void log_message(int priority, const char *fmt, ...);
void dbusAssertError(int r, char* err);
void dbusAssertFailure(int r, char* err);


/******************************************************************************/


void log_message(int priority, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vsyslog(priority, fmt, args);
	vfprintf((priority > LOG_WARNING ? stdout : stderr), fmt, args);
	va_end(args);
}


void dbusAssertError(int r, char* err) {
    if (r < 0)
        log_message(LOG_ERR, "%s %s\n", err, strerror(-r));
    return;
}


void dbusAssertFailure(int r, char* err) {
    if (r < 0) {
        log_message(LOG_ERR, "%s %s\n", err, strerror(-r));
        exit(0);
    }
    return;
}


/******************************************************************************/


static int lastest_image(sd_bus_message *m, void *systemdata, sd_bus_error *ret_error) {
    char file_name[20];
    if(get_image(file_name) != 0)
        log_message(LOG_ERR, "Get image failed");
    if(realpath(file_name, file_path) == NULL)
        log_message(LOG_ERR, "latest image file path error.");

    return sd_bus_reply_method_return(m, "s", file_path);
}


static const sd_bus_vtable method_vtable[] = {
        SD_BUS_VTABLE_START(0),
        SD_BUS_METHOD("LatestImage", NULL, "s", lastest_image, SD_BUS_VTABLE_UNPRIVILEGED),
        SD_BUS_VTABLE_END
};


int main(int argc, char *argv[]) {
    char *pid_file = DEFAULT_PID_FILE;
    FILE *run_fp = NULL;
    pid_t pid = 0, sid = 0;
    bool daemon_flag = false;
    int r;
    char c;

    // Command line argument processing
    while ((c = getopt(argc, argv, "d")) != -1) {
        switch (c) {
            case 'd':
                daemon_flag = true;
                break;
            case '?':
                log_message(LOG_ERR, "Uknown flag\n");
                exit(1);
            default:
                log_message(LOG_ERR, "Usage: %s [-d]\n", argv[0]);
                exit(1);
        }
    }

    if(getuid() != 0) {
        printf("This uses system dbus. Run as root.\n");
        return 1;
    }

    setlogmask(LOG_UPTO(LOG_NOTICE));
    openlog(argv[0], LOG_PID|LOG_CONS, LOG_DAEMON);

    /* Run as daemon if needed */
    if (daemon_flag) {
        log_message(LOG_DEBUG, "Starting as daemon...\n");
        /* Fork */
        if ((pid = fork()) < 0) {
            log_message(LOG_ERR, "Error: Failed to fork!\n");
            exit(EXIT_FAILURE);
        }

        /* Parent process exits */
        if (pid) {
            exit(EXIT_SUCCESS);
        }

        /* Child process continues on */
        /* Log PID */
        if ((run_fp = fopen(pid_file, "w+")) == NULL) {
            log_message(LOG_ERR, "Error: Unable to open file %s\n", pid_file);
            exit(EXIT_FAILURE);
        }
        fprintf(run_fp, "%d\n", getpid());
        fflush(run_fp);
        fclose(run_fp);

        /* Create new session for process group leader */
        if ((sid = setsid()) < 0) {
            log_message(LOG_ERR, "Error: Failed to create new session!\n");
            exit(EXIT_FAILURE);
        }

        /* Set default umask and cd to root to avoid blocking filesystems */
        umask(0);
        if (chdir("/") < 0) {
            log_message(LOG_ERR, "Error: Failed to chdir to root: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        /* Redirect std streams to /dev/null */
        if (freopen("/dev/null", "r", stdin) == NULL) {
            log_message(LOG_ERR, "Error: Failed to redirect streams to /dev/null!\n");
            exit(EXIT_FAILURE);
        }
        if (freopen("/dev/null", "w+", stdout) == NULL) {
            log_message(LOG_ERR, "Error: Failed to redirect streams to /dev/null!\n");
            exit(EXIT_FAILURE);
        }
        if (freopen("/dev/null", "w+", stderr) == NULL) {
            log_message(LOG_ERR, "Error: Failed to redirect streams to /dev/null!\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Connect to the bus */
    r = sd_bus_open_system(&bus);
    dbusAssertFailure(r, "Failed to connect to system bus.");

    /* Take a well-known service //name so that clients can find us */
    r = sd_bus_request_name(bus, BUS_NAME, SD_BUS_NAME_REPLACE_EXISTING);
    dbusAssertFailure(r, "Failed to acquire service name.");

    /* Install the object */
    r = sd_bus_add_object_vtable(bus,
                                 &slot,
                                 OBJECT_PATH,
                                 DESTINATION,
                                 method_vtable,
                                 NULL);
    dbusAssertFailure(r, "Failed to issue method call:");

    while(endProgram == 0) {
        /* Process requests */
        r = sd_bus_process(bus, NULL);
        dbusAssertError(r, "Failed to process bus:");

        if (r > 0) /* we processed a request, try to process another one, right-away */
            continue;

        /* Wait for the next request to process */
        r = sd_bus_wait(bus, (uint64_t) -1);
        dbusAssertError(r, "Failed to wait on bus:");
    }

    r = sd_bus_release_name(bus, BUS_NAME);
    dbusAssertError(r, "Failed to release service name.");
    sd_bus_slot_unref(slot);
    sd_bus_unref(bus);

    return 0;
}



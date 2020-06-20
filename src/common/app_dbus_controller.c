/**
 * The dbus controller for all apps.
 *
 * @file        app_dbus_controller.c
 * @ingroup     app_dbus_controller
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "log_message.h"
#include "app_dbus_controller.h"


#ifdef DEBUG_MODE
/** Dbus destionation for CANdaemon test/debug connection */
#define DESTINATION     "org.OreSat.CANdaemon"
/** Dbus destionation for CANdaemon test/debug connection */
#define INTERFACE_NAME  DESTINATION
/** Dbus object path for CANdaemon test/debug connection */
#define OBJECT_PATH     "/org/OreSat/CANdaemon"
#endif


/** Hold all the app dbus info */
extern app_dbus_data_t      APPS_DBUS;
#ifdef DEBUG_MODE
/** Dbus vtable for the object dictionary app/ */
static const sd_bus_vtable candaemon_vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_METHOD("ReadOD", "qq", "iay", read_OD, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_METHOD("WriteOD", "qqiay", "i", write_OD, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_VTABLE_END
};
#endif


int
apps_dbus_start() {
    int r;

    // open bus
    r = sd_bus_open_system(&APPS_DBUS.bus);
    if(r < 0)
        log_message(LOG_CRIT, "Open system bus for apps failed\n");

#ifdef DEBUG_MODE
    // Take a well-known service name so that clients can find us
    r = sd_bus_request_name(APPS_DBUS.bus, CANDAEMON_DESTINATION, SD_BUS_NAME_ALLOW_REPLACEMENT);
    if(r < 0)
        log_message(LOG_CRIT, "Failed to acquire service name.\n");

    // Install the CANdaemon vtable
    r = sd_bus_add_object_vtable(
            APPS_DBUS.bus,
            NULL,
            OBJECT_PATH,
            INTERFACE_NAME,
            candaemon_vtable,
            NULL);
    if(r < 0)
        log_message(LOG_CRIT,"Failed to add vtable\n");
#endif

    return r;
}


int
apps_dbus_main() {
    int r;
    APPS_DBUS.loop_running = true;

    while(APPS_DBUS.loop_running) {
        // Process requests
        r = sd_bus_process(APPS_DBUS.bus, NULL);
        if(r < 0)
            log_message(LOG_ERR, "Process bus failed for apps\n");
        else if (r > 0) // processed a request, try to process another one right-away
            continue;

        // Wait for the next request to process
        if(sd_bus_wait(APPS_DBUS.bus, UINT64_MAX) < 0)
            log_message(LOG_ERR, "Bus wait failed for apps\n");
    }

    APPS_DBUS.loop_running = false;
    return 1;
}


int
apps_dbus_end() {
    APPS_DBUS.loop_running = false;

#ifdef DEBUG_MODE
    // relase dbus server name
    int r = sd_bus_release_name(APPS_DBUS.bus, CANDAEMON_DESTINATION);
    if(r < 0)
        log_message(LOG_CRIT, "Failed to release service name.");
#endif

    // close bus
    if(APPS_DBUS.bus == NULL) {
        sd_bus_unref(APPS_DBUS.bus);
        APPS_DBUS.bus = NULL;
    }

    return 1;
}


#ifdef DEBUG_MODE
int
read_OD(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    int r;
    uint16_t index, subindex, buf_len = 0;
    uint8_t *buf = NULL;

    // get data
    r = sd_bus_message_read(m, "qq", &index, &subindex);
    if(r < 0)
        log_message(LOG_ERR,"Failed to parse parameters\n");

    // read from OD
    r = app_OD_read(index, subindex, buf, &buf_len);
    if(r != 0)
        log_message(LOG_ERR,"Failed to read from OD\n");

    // send buffer
    return sd_bus_reply_method_return(m, "qay", &buf_len, buf);
}


int
write_OD(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    int r;
    uint16_t index, subindex, OD_len, buf_len;
    uint8_t *buf = NULL;

    r = sd_bus_message_read(m, "qqiay", &index, &subindex, &buf_len, buf);
    if(r < 0)
        log_message(LOG_ERR,"Failed to parse parameters\n");

    // get size
    OD_len = app_OD_get_length(index, subindex);
    if(OD_len < 0)
        log_message(LOG_ERR,"Failed to parse parameters\n");
    if(OD_len < buf_len)
        log_message(LOG_ERR,"Data will not fit\n");

    //write from OD
    r = app_OD_write(index, subindex,buf, buf_len);
    if(r != 0)
        log_message(LOG_ERR,"Failed to write to OD\n");

    // send buffer
    return sd_bus_reply_method_return(m, "s", "done");
}
#endif

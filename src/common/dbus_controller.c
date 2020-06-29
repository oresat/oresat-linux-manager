/**
 * The dbus controller for all apps.
 *
 * @file        dbus_controller.c
 * @ingroup     dbus_controller
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#include "log_message.h"
#include "dbus_controller.h"
#include "apps.h"


#ifdef DEBUG_MODE
/** Dbus destionation for CANdaemon test/debug connection */
#define DESTINATION     "org.OreSat.CANdaemon"
/** Dbus destionation for CANdaemon test/debug connection */
#define INTERFACE_NAME  DESTINATION
/** Dbus object path for CANdaemon test/debug connection */
#define OBJECT_PATH     "/org/OreSat/CANdaemon"
#endif


/** GLOBAL to hold all the app dbus info */
dbus_data_t      APP_DBUS;
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
dbus_controller_init() {
    int r;

    // open bus
    r = sd_bus_open_system(&APP_DBUS.bus);
    if(r < 0)
        log_message(LOG_CRIT, "Open system bus for apps failed\n");

#ifdef DEBUG_MODE
    // Take a well-known service name so that clients can find us
    r = sd_bus_request_name(APP_DBUS.bus, CANDAEMON_DESTINATION, SD_BUS_NAME_ALLOW_REPLACEMENT);
    if(r < 0)
        log_message(LOG_CRIT, "Failed to acquire service name.\n");

    // Install the CANdaemon vtable
    r = sd_bus_add_object_vtable(
            APP_DBUS.bus,
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
dbus_controller_setup_apps() {
    int r = 0;

    r += system_apps_setup();
    r += board_apps_setup();

    return r;
}



int
dbus_controller_loop() {
    int r;
    APP_DBUS.loop_running = true;

    while(APP_DBUS.loop_running) {
        // Process requests
        r = sd_bus_process(APP_DBUS.bus, NULL);
        if(r < 0)
            log_message(LOG_ERR, "Process bus failed for apps\n");
        else if (r > 0) // processed a request, try to process another one right-away
            continue;

        // Wait for the next request to process
        if(sd_bus_wait(APP_DBUS.bus, UINT64_MAX) < 0)
            log_message(LOG_ERR, "Bus wait failed for apps\n");
    }

    APP_DBUS.loop_running = false;
    return 1;
}


int
dbus_controller_end() {
    APP_DBUS.loop_running = false;

#ifdef DEBUG_MODE
    // relase dbus server name
    int r = sd_bus_release_name(APP_DBUS.bus, CANDAEMON_DESTINATION);
    if(r < 0)
        log_message(LOG_CRIT, "Failed to release service name.");
#endif

    // close bus
    if(APP_DBUS.bus == NULL) {
        sd_bus_unref(APP_DBUS.bus);
        APP_DBUS.bus = NULL;
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

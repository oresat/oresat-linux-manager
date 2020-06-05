#include "log_message.h"
#include "app_OD_helpers.h"
#include "file_transfer.h"
#include "app_dbus_controller.h"
#include "sdr_gps_app.h"
#include <systemd/sd-bus.h>
#include <stdint.h>


#define DESTINATION         "org.OreSat.GPS"
#define INTERFACE_NAME      "org.OreSat.GPS"
#define OBJECT_PATH         "/org/OreSat/GPS"
#define APP_NAME            "GPS"
#define SDR_GPS_OD_INDEX    0x3100


extern app_dbus_data_t      APPS_DBUS;


// Static functions headers
static int read_gps_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error);


/*****************************************************************************/
// app ODF and dbus functions


int
sdr_gps_dbus_signal_match() {
    int r;

    r = sd_bus_match_signal(
            APPS_DBUS.bus,
            NULL,
            NULL,
            OBJECT_PATH,
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            read_gps_cb,
            NULL);
    if (r < 0) {
        app_log_message(APP_NAME, LOG_ERR, "Failed to add PropertiesChanged signal match.\n");
        return r;
    }

    return 1;
}


/*****************************************************************************/
// app callback functions


static int
read_gps_cb(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
    int r;
    int32_t state;
    int16_t posX = 0;
    int16_t posY = 0;
    int16_t posZ = 0;
    int16_t velX = 0;
    int16_t velY = 0;
    int16_t velZ = 0;

    r = sd_bus_message_read(m, "i", &state);
    if (r < 0)
        return -1;

    r = sd_bus_message_read(m, "ddd", &posX, &posY, &posZ);
    if (r < 0)
        return -1;

    r = sd_bus_message_read(m, "ddd", &velX, &velY, &velZ);
    if (r < 0)
        return -1;

    app_OD_write(SDR_GPS_OD_INDEX, 1, &state, sizeof(int32_t));
    app_OD_write(SDR_GPS_OD_INDEX, 2, &posX, sizeof(float));
    app_OD_write(SDR_GPS_OD_INDEX, 3, &posY, sizeof(float));
    app_OD_write(SDR_GPS_OD_INDEX, 4, &posZ, sizeof(float));
    app_OD_write(SDR_GPS_OD_INDEX, 5, &velX, sizeof(float));
    app_OD_write(SDR_GPS_OD_INDEX, 6, &velY, sizeof(float));
    app_OD_write(SDR_GPS_OD_INDEX, 7, &velZ, sizeof(float));

    return 0;
}



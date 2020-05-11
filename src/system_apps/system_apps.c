#include "system_apps.h"
#include "app_OD_helpers.h"
#include "daemon_controller.h"
#include "file_transfer_ODF.h"
#include "linux_updater_app.h"
#include "power_management_app.h"


#define POWER_MANAGEMENT_ODF_INDEX  0x3000
#define UPDATER_ODF_INDEX           0x3004

#define BOARD "gps" // TODO fix cmake

int setup_system_apps() {
    // power mangament
    app_OD_configure(POWER_MANAGEMENT_ODF_INDEX, power_management_ODF, NULL, 0, 0U);

    // Linux updater
    app_OD_configure(UPDATER_ODF_INDEX, updater_ODF, NULL, 0, 0U);
    app_register_daemon("Linux Updater", "oresat-linux-updaterd.service");
    app_add_request_recv_file(
            "Linux Updater",
            "^("BOARD"\\-update\\-\\d{4}\\-\\d{2}\\-\\d{2}\\-\\d{2}\\-\\d{2}\\.tar\\.gz)$",
            "/tmp/oresat-linux-updater/cache/",
            NULL);
    linux_updater_dbus_signal_match();


    return 1;
}

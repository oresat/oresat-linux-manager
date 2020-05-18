#include "board_apps.h"
#include "app_OD_helpers.h"
#include "daemon_controller.h"
#include "file_transfer_ODF.h"
#include "star_tracker_app.h"


int
setup_board_apps() {
    // Star Tracker app
    star_tracker_dbus_signal_match();
    app_register_daemon("star-tracker","oresat-star-tracker.service");

    return 1;
}

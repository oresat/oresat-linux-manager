#include "board_apps.h"
#include "app_OD_helpers.h"
#include "daemon_controller.h"
#include "file_transfer.h"


int
setup_board_apps() {
    // Star Tracker app
    star_tracker_dbus_signal_match();
 *  app_register_daemon("star_tracker","oresat-startracker.service////////////////")

    return 1;
}

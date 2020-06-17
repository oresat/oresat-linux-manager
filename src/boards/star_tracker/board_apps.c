#include "apps.h"


int
setup_board_apps() {
    // Star Tracker app
    star_tracker_dbus_signal_match();
 *  app_register_daemon("star_tracker","oresat-startracker.service////////////////")

    return 1;
}

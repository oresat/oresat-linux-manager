#include "apps.h"


int
board_apps_setup() {
    // Star Tracker app
    star_tracker_dbus_signal_match();
 *  app_register_daemon("star_tracker","oresat-startracker.service////////////////")

    return 1;
}

#include "apps.h"
#include "star_tracker_app.h"


int
board_apps_setup() {
    int r;

    r = star_tracker_app_setup();

    return r;
}

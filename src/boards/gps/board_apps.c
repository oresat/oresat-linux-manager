#include "sdr_gps_app.h"


int
setup_board_apps() {

    //SDR GPS app
    sdr_gps_dbus_signal_match();

    // ADCS app
    //adcs_dbus_signal_match();

    return 0;
}

#include "apps.h"
#include "pru_camera_test_app.h"

#define PRU_CAMERA_TEST_ODF_INDEX  0x3100

#define BOARD "cirrus_flux_camera" // TODO fix cmake

int
board_apps_setup() {

    // pru camera test app
    app_OD_configure(PRU_CAMERA_TEST_ODF_INDEX, PRU_CAMERA_TEST_ODF, NULL, 0, 0U);

    return 1;
}

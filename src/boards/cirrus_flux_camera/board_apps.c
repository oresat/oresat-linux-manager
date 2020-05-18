#include "board_apps.h"
#include "app_OD_helpers.h"
#include "daemon_controller.h"
#include "file_transfer_ODF.h"
#include "pru_camera_test_app.h"

#define PRU_CAMERA_TEST_ODF_INDEX  0x3100

#define BOARD "cirrus_flux_camera" // TODO fix cmake

int
setup_board_apps() {

    // pru camera test app
    app_OD_configure(PRU_CAMERA_TEST_ODF_INDEX, PRU_CAMERA_TEST_ODF, NULL, 0, 0U);

    return 1;
}

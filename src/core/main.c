#include "olm_app.h"
#include "linux_updater_app.h"


int
main() {
    olm_app_t *app =  linux_updater_app_create();
    olm_app_free(app);
    return 0;
}

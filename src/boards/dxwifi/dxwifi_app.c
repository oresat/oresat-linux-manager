
#include "CANopen.h"
#include "olm_file_cache.h"
#include "dxwifi_app.h"
#include <stdbool.h>

void
dxwifi_app_async(void *data, olm_file_cache_t *fread_cache) {
    CO_LOCK_OD();
    OD_dxWiFiStatus = true;
    CO_UNLOCK_OD();
}

void
dxwifi_app_end(void *data) {
    CO_LOCK_OD();
    OD_dxWiFiStatus = false;
    CO_UNLOCK_OD();
}

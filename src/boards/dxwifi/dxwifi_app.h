#ifndef DXWIFI_APP_H
#define DXWIFI_APP_H

#include "olm_file_cache.h"

void dxwifi_app_async(void *data, olm_file_cache_t *fread_cache);

void dxwifi_app_end(void *data);

#endif /* DXWIFI_APP_H */

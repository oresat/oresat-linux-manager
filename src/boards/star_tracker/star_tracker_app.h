#ifndef STAR_TRACKER_APP_H
#define STAR_TRACKER_APP_H

#include "olm_file_cache.h"
#include "star_tracker.h"

void star_tracker_app_async(void *data, olm_file_cache_t *fread_cache);

void star_tracker_app_end(void *data);

#endif /* STAR_TRACKER_APP_H */

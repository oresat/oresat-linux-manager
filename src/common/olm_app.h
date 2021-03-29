#ifndef OLM_APP_H
#define OLM_APP_H

#include "utility.h"
#include <stdlib.h>
#include <stddef.h>

enum active_states {
    unit_inactive = 0,
    unit_reloading = 1,
    unit_active = 2,
    unit_failed = 3, 
    unit_activating = 4,
    unit_deactivating = 5,
};

/**
 * All the data an app must provide to OLM's core. 
 *
 * All apps must a function to make (with malloc) and fill this struct out.
 */
typedef struct {
    /** The app's name. */
    char *name;
    /**
     * The unit name for the daemon the app is interfacing to. The ".service"
     * is required.
     */
    char *service_file;
    /**
     * The unit object path for the org.freedesktop.systemd1.Unit interface.
     * OLM's App Manager will fill this out if service_file is set.
     */
    char *unit_object_path;
    /**
     * The active state of the unit. @ref active_states. Will be set by OLM's
     * App Manager.
     */
    int unit_active_state;
    /**
     * If a new file recieve by OLM matches this keyword, the callback function
     * will be called. Set to NULL if app doesn't want to recieve file from
     * the CANbus.
     */
    char *fwrite_keyword;
    /**
     * Callback function used when fwrite_keyword is set. Must be set 
     * fwrite_keyword is set and will be ingored if fwrite_keyword is
     * not set.
     */
    int (*fwrite_cb)(const char *filepath);
    /**
     * The app's private data. Optional, set to NULL if not needed. This will
     * be argument to free_data_cb().
     */
    void *data;
    /**
     * The function to cleanup the app's private data. Set to NULL if not
     * needed, otherwise this function is called when the app is no longer
     * needed.
     */
    int (*data_free_cb)(void *data);
} olm_app_t;

#define OLM_APP_DEFAULT {\
        .name = NULL, \
        .service_file = NULL, \
        .fwrite_keyword = NULL, \
        .unit_object_path = NULL, \
        .unit_active_state = unit_inactive, \
        .fwrite_cb = NULL, \
        .data = NULL, \
        .data_free_cb = NULL, \
    }

#define OLM_APP_FREE(app) \
    if (app != NULL) { \
        FREE(app->name); \
        FREE(app->service_file); \
        FREE(app->unit_object_path); \
        FREE(app->fwrite_keyword);\
        if (app->data != NULL) \
            app->data_free_cb(app->data); \
    } 

#endif /* OLM_APP_H */

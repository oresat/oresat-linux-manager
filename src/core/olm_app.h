#ifndef OLM_APP_H
#define OLM_APP_H

#include "utility.h"
#include <stdlib.h>
#include <stddef.h>

/**
 * All the data an app must provide to OLM's core. 
 *
 * All apps must a #define to initialize this struct with the information for
 * that app.
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

#define OLM_APP_INITIALIZER { \
    .name = NULL; \
    .service_file = NULL; \
    .fwrite_keyword = NULL; \
    .unit_object_path = NULL; \
    .unit_active_state = 0; \
    .fwrite_cb = NULL; \
    .data = NULL; \
    .data_free_cb = NULL; \
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

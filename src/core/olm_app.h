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
     * The systemd's service file name for the app. The ".service" is
     * required.
     */
    char *service_file;
    /**
     * If a new file recieve by OLM match this keyword, the callback function
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

#define OLM_APP_MALLOC_AND_NULL(app) \
    if ((app = malloc(sizeof(olm_app_t))) != NULL) { \
        app->name = NULL; \
        app->service_file = NULL; \
        app->fwrite_keyword = NULL; \
        app->fwrite_cb = NULL; \
        app->data = NULL; \
        app->data_free_cb = NULL; \
    } \

#define OLM_APP_FREE(app) \
    if (app != NULL) { \
        FREE(app->name); \
        FREE(app->service_file); \
        FREE(app->fwrite_keyword);\
        if (app->data != NULL) \
            app->data_free_cb(app->data); \
        free(app); \
    } 

#endif /* OLM_APP_H */

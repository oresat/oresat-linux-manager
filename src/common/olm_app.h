#ifndef OLM_APP_H
#define OLM_APP_H

#include "utility.h"
#include <stdlib.h>
#include <stddef.h>

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
} olm_app_t;

#define OLM_APP_DEFAULT {\
        .name = NULL, \
        .service_file = NULL, \
        .fwrite_keyword = NULL, \
        .fwrite_cb = NULL, \
    }

#define OLM_APP_FREE(app) \
    if (app != NULL) { \
        FREE(app->name); \
        FREE(app->service_file); \
        FREE(app->fwrite_keyword);\
    } 

#endif /* OLM_APP_H */

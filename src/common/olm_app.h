/**
 * A structs for defining an OLM App.
 *
 * @file        olm_app.h
 * @ingroup     common
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef OLM_APP_H
#define OLM_APP_H

#include "olm_file_cache.h"

/** Systemd daemon states. */
typedef enum {
    UNIT_INACTIVE = 0,
    UNIT_RELOADING = 1,
    UNIT_ACTIVE = 2,
    UNIT_FAILED = 3,
    UNIT_ACTIVATING = 4,
    UNIT_DEACTIVATING = 5,
    UNIT_UNKNOWN = 6, // No unit
} unit_active_states_t;

/** Systemd commands for daemons. */
typedef enum {
    UNIT_NO_CMD = 0, // No command, do nothing
    UNIT_STOP = 1,
    UNIT_START = 2,
    UNIT_RESTART = 3,
} unit_commands_t;

/** OLM App info. */
typedef struct {
    /** The app's name. */
    const char *name;
    /** The systemd unit name for the app. The ".service" is required. */
    const char *unit_name;
    /**
     * The systemd1 object path for systemd unit. App Manager will fill this
     * out.
     */
    char *unit_systemd1_object_path;
    /** State the unit is in. App Manager will keep this up to date. */
    unit_active_states_t unit_state;
    /** Command the App Manager will parser. Private to App Manager. */
    unit_commands_t unit_command;
    /**
     * If a new file recieve by OLM matches this keyword, the callback function
     * will be called. Set to NULL if app doesn't want to recieve file from
     * the CANbus.
     */
    const char *fwrite_keyword;
    /**
     * Callback function used when fwrite_keyword is set. Must be set 
     * fwrite_keyword is set and will be ingored if fwrite_keyword is
     * not set.
     */
    int (*fwrite_cb)(const char *filepath);
    /**
     * Callback function called in async loop thread. Will only be called when
     * daemon is in UNIT_ACTIVE state. Set to NULL if not needed.
     */
    void (*async_cb)(void *data, olm_file_cache_t *fread_cache);
    /**
     * Callback function called when daemon has transition from UNIT_ACTIVE
     * state to another state. Useful to set OD values and/or make sure
     * hardware is in correct state. Set to NULL if not needed.
     */
    void (*daemon_end_cb)(void *data);
    /**
     * Pointer to private data to be the input to @ref async_cbi and @ref
     * daemon_end_cb. Useful for sharing data between the ODF and async_cb
     * functions. Set to NULL if not needed.
     */
    void *data;
} olm_app_t;

#endif /* OLM_APP_H */

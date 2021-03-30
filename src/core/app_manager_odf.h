/**
 * App Manager ODF.
 *
 * @file        app_manager_odf.h
 * @ingroup     app_manager_odf
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for apps running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef APP_MANAGER_ODF_H
#define APP_MANAGER_ODF_H

#include "CANopen.h"
#include "board_main.h"
#include <stdbool.h>

/** Systemd commands for apps. */
enum unit_commands {
    /** No command, do nothing. */
    UNIT_NO_CMD = 0,
    /** Stop the unit. */
    UNIT_STOP = 1,
    /** Start the unit. */
    UNIT_START = 2,
    /** Restart the unit. */
    UNIT_RESTART = 3,
};

/** Info and controls for a app's service unit that is not in OD. */
typedef struct {
    /** The systemd1 object path for system unit. */
    char *systemd_object_path;
    /** State the unit is in, see @ref active_states. */
    int state;
    /**
     * Command todo onto the unit, see @ref unit_commands. This is seperate
     * from state as commmand will be handle asynchronously in @ref
     * app_manager_async.
     */
    int command;
} unit_t;

/** Privae data used by the App Manager. */
typedef struct {
    /** The configuration for the OLM for this sepecfic board. */
    olm_board_t *board;
    /** Unit info/controls to be shared between the ODF and async function */
    unit_t *units;
    /**
     * A flag for enabling/disabling cpufreq control. If enable the cpufreq
     * governor will be set to "performance" if any units in the running active
     * state, otherwise the cpufreq governor will be set to "power_save".
     */
    bool cpufreq_control;
} app_manager_t;

/**
 * @breif Initalize an @ref app_manager_t object for @ref app_manager_async and
 * @ref app_manager_odf
 *
 * @param app_manager @ref app_manager_t object to fill out.
 * @param board @ref olm_board_t board configurations to use.
 * @param cpufreq_ctrl Set to true if the app manager should change the cpufreq
 * governor when units are stoped/stared.
 *
 * @return 1 on success or negative errno on failure.
 */
int app_manager_init(app_manager_t *app_manager, olm_board_t *board, bool cpufreq_ctrl);

/** @breif App Manager function to be called in the async thread/loop. */
void app_manager_async(app_manager_t *app_manager);

/**
 * Object Dictionary Function for app contoller OD entry.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t app_manager_ODF(CO_ODF_arg_t *ODF_arg);

#endif /* APP_MANAGER_ODF_H */

/**
 * App Manager ODF.
 *
 * @file        app_manager_odf.c
 * @ingroup     app_manager_odf
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for apps running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

//#include "cpufreq.h"
#include "log_message.h"
#include "systemd_app.h"
#include "board_main.h"
#include "olm_file_cache.h"
#include "app_manager_odf.h"
#include <errno.h>
#include <linux/limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/syslog.h>

/**
 * @breif Save power when no other OreSat daaemons are running.
 *
 * If all the app are stopped sets the cpufreq governor to powersave mode
 * or if any OreSat app is running sets the cpufreq governor to performance
 * mode.
 */
/*
static void
save_power(void) {
    int cur_stop = 0;

    for(unsigned int i=0; i<app_count; ++i) {
        if (app_list[i].status ==  STOPPED)
            ++cur_stop;
    }

    if (cur_stop == 0)
        set_cpufreq_gov(powersave);
    else
        set_cpufreq_gov(performance);
}*/


int
app_manager_init(app_manager_t *app_manager, olm_board_t *board, bool cpufreq_ctrl) { 
    if (app_manager == NULL)
        return -EINVAL;

    app_manager->board = board;

    if (board != NULL) {
        app_manager->units = malloc(sizeof(unit_t) * board->apps_len);

        if (app_manager->units != NULL) {
            // find systemd object path and set all default values
            for (int i=0; i<board->apps_len; ++i) {
                app_manager->units[i].systemd_object_path = get_unit(board->apps[i].service_file);
                app_manager->units[i].state = unit_inactive;
                app_manager->units[i].command = UNIT_NO_CMD;
            }
                
        }
    } else {
        app_manager->units = NULL;
    }

    app_manager->cpufreq_control = cpufreq_ctrl;

    return 1;
}

void
app_manager_async(app_manager_t *app_manager, olm_file_cache_t *fwrite_cache) {
    char path[PATH_MAX];
    unit_t *unit = NULL;
    olm_app_t *app = NULL;
    olm_file_t *file;
    int files;
    int r;

    if (app_manager == NULL || fwrite_cache == NULL) {
        log_message(LOG_CRIT, "missing input data in app_manager_async()");
        return;
    }

    for (int i=0; i<app_manager->board->apps_len; ++i) {
        app = &app_manager->board->apps[i];
        unit = &app_manager->units[i];

        // deal with change state command
        switch (unit->command) {
            case UNIT_NO_CMD:
                break;
            case UNIT_START:
                log_message(LOG_INFO, "starting %s", app->service_file);
                start_unit(unit->systemd_object_path);
                break;
            case UNIT_STOP:
                log_message(LOG_INFO, "stoping %s", app->service_file);
                stop_unit(unit->systemd_object_path);
                break;
            case UNIT_RESTART:
                log_message(LOG_INFO, "restarting %s", app->service_file);
                restart_unit(unit->systemd_object_path);
                break;
            default: // this should not happen
                log_message(LOG_ERR, "unknown state %d", app_manager->units[i].state);
        }

        unit->command = UNIT_NO_CMD;

        // update state
        unit->state = get_active_state_unit(unit->systemd_object_path);

        if (app->fwrite_keyword == NULL || app->fwrite_cb || unit->state != unit_active)
            continue;

        // send file(s) from fwrite cache to daemon
        files = olm_file_cache_len(fwrite_cache, app->fwrite_keyword);
        for (int j=0; j<files; ++j) { // iterate thru file with app's keyword
            olm_file_cache_index(fwrite_cache, i, app->fwrite_keyword, &file);
            sprintf(path, "%s%s", fwrite_cache->dir, file->name);

            r = app->fwrite_cb(path);
            if ((r = app->fwrite_cb(path)) == 0) {
                log_message(LOG_DEBUG, "%s cannot recieve %s right now", app->service_file, file->name);
                continue;
            } else if (r < 0) {
                log_message(LOG_CRIT, "%s cannot recieve %s", app->service_file, file->name);
            }

            log_message(LOG_INFO, "deleting %s from fwrite cache", file->name);
            if (olm_file_cache_remove(fwrite_cache, file->name) >= 0)
                --j; // adjust for the removed file
        }
    }
}

CO_SDO_abortCode_t
app_manager_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    app_manager_t *app_manager = (app_manager_t *)ODF_arg->object;
    olm_app_t *app = NULL;
    unit_t *unit = NULL;
    uint8_t temp_uint8;;

    if (app_manager == NULL || app_manager->board == NULL || \
            app_manager->board->apps == NULL)
        return CO_SDO_AB_NO_DATA;

    unit = &app_manager->units[OD_appManager.selectApp];
    app = &app_manager->board->apps[OD_appManager.selectApp];

    switch (ODF_arg->subIndex) {
        case OD_3005_2_appManager_selectApp: // app selector, uint8, readwrite

            // make sure input is valid
            if (!ODF_arg->reading) {
                temp_uint8 = CO_getUint8(ODF_arg->data);
                if (temp_uint8 > app_manager->board->apps_len)
                    ret = CO_SDO_AB_GENERAL; //TODO

                OD_appManager.daemonState = get_active_state_unit(unit->systemd_object_path);
            }

            break;

        case OD_3005_3_appManager_appName: // app name, domain, readonly

            if (ODF_arg->reading) {
                if (app->name == NULL) {
                    ret = CO_SDO_AB_NO_DATA;
                } else {
                    ODF_arg->dataLength = strlen(app->name)+1;
                    memcpy(ODF_arg->data, app->name, ODF_arg->dataLength);
                }
            } else {
                ret = CO_SDO_AB_READONLY;
            }

            break;

        case OD_3005_4_appManager_daemonState: // app's daemon state, uint8, readwrite

            // make sure input is valid
            if (!ODF_arg->reading) {
                temp_uint8 = CO_getUint8(ODF_arg->data);
                if (temp_uint8 <= UNIT_RESTART)
                    unit->command = temp_uint8;
                else
                    ret = CO_SDO_AB_GENERAL; //TODO
            }

            break;
    }

    return ret;
}

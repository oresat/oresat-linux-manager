/**
 * OLM app manager.
 *
 * @file        app_manager_odf.c
 * @ingroup     app_manager_odf
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for apps running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

//#include "cpufreq.h"
#include "logging.h"
#include "systemd.h"
#include "board_main.h"
#include "olm_file_cache.h"
#include "olm_app.h"
#include "app_manager.h"
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
app_manager_init(olm_app_t **apps) { 
    int i;

    if (apps == NULL)
        return -EINVAL;

    // find systemd1 object paths
    for (i=0; apps[i] != NULL; ++i) {
        apps[i]->unit_systemd1_object_path = get_unit(apps[i]->unit_name);
        apps[i]->unit_state = UNIT_INACTIVE;
        apps[i]->unit_command = UNIT_NO_CMD;
    }

    CO_LOCK_OD();
    OD_appManager.totalApps = (uint8_t)i;
    CO_UNLOCK_OD();

    return 1;
}

void
app_manager_async(olm_app_t **apps, olm_file_cache_t *fwrite_cache) {
    char path[PATH_MAX];
    olm_file_t *file;
    uint32_t active_apps = 0, failed_apps = 0;
    int files, r;

    if (apps == NULL) {
        log_printf(LOG_DEBUG, "missing apps input");
        return;
    }

    for (int i=0; apps[i] != NULL; ++i) {
        if (apps[i]->unit_systemd1_object_path == NULL ||
                apps[i]->unit_state == UNIT_UNKNOWN) {
            continue; // no daemon found 
        }

        // deal with change state command
        switch (apps[i]->unit_command) {
            case UNIT_NO_CMD:
                break;
            case UNIT_START:
                log_printf(LOG_INFO, "starting %s", apps[i]->unit_name);
                start_unit(apps[i]->unit_systemd1_object_path);
                break;
            case UNIT_STOP:
                log_printf(LOG_INFO, "stoping %s", apps[i]->unit_name);
                stop_unit(apps[i]->unit_systemd1_object_path);
                break;
            case UNIT_RESTART:
                log_printf(LOG_INFO, "restarting %s", apps[i]->unit_name);
                restart_unit(apps[i]->unit_systemd1_object_path);
                break;
            default: // this should not happen
                log_printf(LOG_ERR, "unknown state %d", apps[i]->unit_state);
        }

        apps[i]->unit_command = UNIT_NO_CMD;

        // update state
        apps[i]->unit_state = get_active_state_unit(apps[i]->unit_systemd1_object_path);

        if (apps[i]->unit_state == UNIT_ACTIVE)
            ++active_apps; 
        else if (apps[i]->unit_state == UNIT_FAILED)
            ++failed_apps; 

        if (fwrite_cache == NULL || apps[i]->fwrite_keyword == NULL ||
                apps[i]->fwrite_cb || apps[i]->unit_state != UNIT_ACTIVE)
            continue;

        // send file(s) from fwrite cache to daemon
        files = olm_file_cache_len(fwrite_cache, apps[i]->fwrite_keyword);
        for (int j=0; j<files; ++j) { // iterate thru file with app's keyword
            olm_file_cache_index(fwrite_cache, i, apps[i]->fwrite_keyword, &file);
            sprintf(path, "%s%s", fwrite_cache->dir, file->name);

            r = apps[i]->fwrite_cb(path);
            if ((r = apps[i]->fwrite_cb(path)) == 0) { // not now
                log_printf(LOG_DEBUG, "%s cannot recieve %s right now", apps[i]->unit_name, file->name);
            } else if (r < 0) { // was successful
                log_printf(LOG_INFO, "deleting %s from fwrite cache", file->name);
                if (olm_file_cache_remove(fwrite_cache, file->name) >= 0)
                    --j; // adjust for the removed file
            } else { // error
                log_printf(LOG_CRIT, "%s cannot recieve %s", apps[i]->unit_name, file->name);
            }

            olm_file_free(file);
        }
    }

    CO_LOCK_OD();
    OD_appManager.activeApps = (uint8_t)active_apps;
    OD_appManager.failedApps = (uint8_t)failed_apps;
    CO_UNLOCK_OD();
}

CO_SDO_abortCode_t
app_manager_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    olm_app_t **apps = (olm_app_t **)ODF_arg->object;
    olm_app_t *app = NULL;
    uint8_t temp_uint8;

    if (apps == NULL)
        return CO_SDO_AB_NO_DATA;

    app = apps[OD_appManager.selectApp];

    switch (ODF_arg->subIndex) {
        case OD_3005_4_appManager_selectApp: // app selector, uint8, readwrite

            // make sure input is valid
            if (!ODF_arg->reading) {
                temp_uint8 = CO_getUint8(ODF_arg->data);
                if (temp_uint8 > OD_appManager.totalApps)
                    ret = CO_SDO_AB_GENERAL; //TODO
            }

            break;

        case OD_3005_5_appManager_appName: // app name, domain, readonly

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

        case OD_3005_6_appManager_daemonState: // app's daemon state, uint8, readwrite

            // make sure input is valid
            if (ODF_arg->reading) {
                CO_setUint32(ODF_arg->data, (uint8_t)app->unit_state);
            } else {
                temp_uint8 = CO_getUint8(ODF_arg->data);
                if (temp_uint8 <= UNIT_RESTART)
                    app->unit_command = temp_uint8;
                else
                    ret = CO_SDO_AB_GENERAL; //TODO
            }

            break;
    }

    return ret;
}

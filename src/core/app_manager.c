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

#include "app_manager.h"
#include "board_main.h"
#include "cpufreq.h"
#include "logging.h"
#include "olm_app.h"
#include "olm_file_cache.h"
#include "systemd.h"
#include <errno.h>
#include <linux/limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/syslog.h>

int
app_manager_init(olm_app_t **apps) {
    int i;

    if (apps == NULL)
        return -EINVAL;

    // find systemd1 object paths
    for (i = 0; apps[i] != NULL; ++i) {
        apps[i]->unit_systemd1_object_path = get_unit(apps[i]->unit_name);
        if (apps[i]->unit_systemd1_object_path == NULL)
            apps[i]->unit_systemd1_object_path = load_unit(apps[i]->unit_name);
        log_printf(LOG_DEBUG, "app %s systemd1 object path %s", apps[i]->name,
                   apps[i]->unit_systemd1_object_path);
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
    uint8_t last_state;
    int files, r;

    if (apps == NULL || fwrite_cache == NULL) {
        log_printf(LOG_DEBUG, "app_manager_async() missing inputs");
        return;
    }

    for (int i = 0; apps[i] != NULL; ++i) {
        if (apps[i]->unit_systemd1_object_path == NULL
            || apps[i]->unit_state == UNIT_UNKNOWN) {
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
        last_state = apps[i]->unit_state;
        apps[i]->unit_state
            = get_unit_active_state(apps[i]->unit_systemd1_object_path);

        // call daemon_end_cb if daemon has stopped / failed
        if (apps[i]->daemon_end_cb != NULL && last_state == UNIT_ACTIVE
            && apps[i]->unit_state != UNIT_ACTIVE)
            apps[i]->daemon_end_cb(apps[i]->data);

        // count failed / active daemons
        if (apps[i]->unit_state == UNIT_ACTIVE)
            ++active_apps;
        else if (apps[i]->unit_state == UNIT_FAILED)
            ++failed_apps;

        // if app is not running or does not require fwrite
        if (apps[i]->unit_state != UNIT_ACTIVE
            || apps[i]->fwrite_keyword == NULL || apps[i]->fwrite_cb == NULL) {
            continue;
        }

        // send file(s) from fwrite cache to daemon
        files = olm_file_cache_len(fwrite_cache, apps[i]->fwrite_keyword);
        if (files > 0) { // iterate thru file with app's keyword
            olm_file_cache_index(fwrite_cache, 0, apps[i]->fwrite_keyword,
                                 &file);
            sprintf(path, "%s%s", fwrite_cache->dir, file->name);
            log_printf(LOG_DEBUG, "send file %s to app", path);

            r = apps[i]->fwrite_cb(path);
            if (r == 0) { // not now
                log_printf(LOG_DEBUG, "%s cannot recieve %s right now",
                           apps[i]->unit_name, file->name);
            } else if (r > 0) { // was successful
                log_printf(LOG_INFO, "deleting %s from fwrite cache",
                           file->name);
                olm_file_cache_remove(fwrite_cache, file->name);
            } else { // error
                log_printf(LOG_CRIT, "%s cannot recieve %s", apps[i]->unit_name,
                           file->name);
            }

            olm_file_free(file);
        }
    }

    if (OD_OLMControl.CPUFrequency) {
        if (active_apps == 0 && OD_systemInfo.CPUGovernor == performance) {
            set_cpufreq_gov(powersave);
            CO_LOCK_OD();
            OD_systemInfo.CPUGovernor = get_cpufreq_gov();
            OD_systemInfo.CPUFrequency = get_cpufreq();
            CO_UNLOCK_OD();
        } else if (active_apps > 0 && OD_systemInfo.CPUGovernor == powersave) {
            set_cpufreq_gov(performance);
            CO_LOCK_OD();
            OD_systemInfo.CPUGovernor = get_cpufreq_gov();
            OD_systemInfo.CPUFrequency = get_cpufreq();
            CO_UNLOCK_OD();
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
                ret = CO_SDO_AB_GENERAL; // TODO
        }

        break;

    case OD_3005_5_appManager_appName: // app name, domain, readonly

        if (ODF_arg->reading) {
            if (app->name == NULL) {
                ret = CO_SDO_AB_NO_DATA;
            } else {
                ODF_arg->dataLength = strlen(app->name) + 1;
                memcpy(ODF_arg->data, app->name, ODF_arg->dataLength);
            }
        } else {
            ret = CO_SDO_AB_READONLY;
        }

        break;

    case OD_3005_6_appManager_daemonState: // app's daemon state, uint8,
                                           // readwrite

        // make sure input is valid
        if (ODF_arg->reading) {
            CO_setUint32(ODF_arg->data, (uint8_t)app->unit_state);
        } else {
            temp_uint8 = CO_getUint8(ODF_arg->data);
            if (temp_uint8 <= UNIT_RESTART)
                app->unit_command = temp_uint8;
            else
                ret = CO_SDO_AB_GENERAL; // TODO
        }

        break;
    }

    return ret;
}

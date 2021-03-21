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
#include "systemd_app.h"
#include "olm_app.h"
#include "app_manager_odf.h"
#include <stdint.h>
#include <string.h>

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

CO_SDO_abortCode_t
app_manager_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;
    olm_app_t *apps = (olm_app_t *)ODF_arg->object;

    if (apps == NULL)
        return CO_SDO_AB_NO_DATA;

    switch (ODF_arg->subIndex) {

        case OD_3005_2_appManager_selectApp: // selected app, uint8, readwrite

            if (!ODF_arg->reading)
                if (CO_getUint8(ODF_arg->data) > OD_appManager.totalApps)
                    ret = CO_SDO_AB_GENERAL; // TODO input must be less than total apps

            break;

        case OD_3005_3_appManager_appName: // app name, domain, readonly

            if (ODF_arg->reading) {
                ODF_arg->dataLength = strlen(apps[OD_appManager.selectApp].name)+1;
                memcpy(ODF_arg->data, apps[OD_appManager.selectApp].name, ODF_arg->dataLength);
            } else {
                ret = CO_SDO_AB_READONLY;
            }

            break;

        case OD_3005_4_appManager_daemonState: // app's daemon state, uint8, readwrite

            if (!ODF_arg->reading) {
                uint8_t command = CO_getUint8(ODF_arg->data);

                if (command != START_DAEMON || command != START_DAEMON || 
                        command != START_DAEMON)
                    ret = CO_SDO_AB_NO_DATA; // TODO
                /*
                if (command == START_DAEMON)
                     start_app(app_list[list_index].service_name);
                else if (command == STOP_DAEMON)
                    stop_app(app_list[list_index].service_name);
                else if (command == RESTART_DAEMON)
                    restart_app(app_list[list_index].service_name);
                else
                    ret = CO_SDO_AB_GENERAL;
                */
            }

            break;
    }

    return ret;
}

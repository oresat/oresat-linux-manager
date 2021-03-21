/**
 * App for the Linux updater dameon.
 *
 * @file        linux_updater_app.c
 * @ingroup     linux_updater_app
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#include "CANopen.h"
#include "linux_updater_app.h"
#include "linux_updater_odf.h"
#include "log_message.h"
#include <linux/limits.h>
#include <stdint.h>

/* Holds the current state of the updater. */
static int32_t              current_state = 0;
/* The number archive files available. */
static uint32_t             updates_available = 0;
/** If an updating, this holds the name of archive file. */
static char                 current_file[PATH_MAX] = "\0";

CO_SDO_abortCode_t
updater_ODF(CO_ODF_arg_t *ODF_arg) {
    CO_SDO_abortCode_t ret = CO_SDO_AB_NONE;

    switch(ODF_arg->subIndex) {
        case 1 : // current state

            if(ODF_arg->reading == true) {
                ODF_arg->dataLength = sizeof(current_state);
                memcpy(ODF_arg->data, &current_state, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, read only

            break;

        case 2 : // updates available

            if(ODF_arg->reading == true) {
                ODF_arg->dataLength = sizeof(updates_available);
                memcpy(ODF_arg->data, &updates_available, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, read only

            break;

        case 3 : // current file

            if(ODF_arg->reading == true)  {
                ODF_arg->dataLength = strlen(current_file);
                memcpy(ODF_arg->data, current_file, ODF_arg->dataLength);
            }
            else
                ret = CO_SDO_AB_READONLY; // can't write parameters, read only

            break;

        case 4 : // TODO REMOVE

            ret = CO_SDO_AB_GENERAL;

            break;

        case 5 : // give updater new file, will not update with it yet

            if(ODF_arg->reading == true) {
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
                break;
            }

            if(ODF_arg->dataLength > PATH_MAX) {
                log_message(LOG_ERR, "New archvie file path wont fit in buffer");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            // copy file name into a temp var
            char new_archive_file_path[PATH_MAX] = "\0";
            memcpy(new_archive_file_path, ODF_arg->data, ODF_arg->dataLength);

            if(new_archive_file_path[0] != '/') {
                log_message(LOG_ERR, "New archive file path not an absolute path");
                ret = CO_SDO_AB_GENERAL;
                break;
            }

            if (linux_updater_app_add_update_file(new_archive_file_path) != 0)
                ret = CO_SDO_AB_GENERAL;

            break;

        case 6 : // start update


            if(ODF_arg->reading == true) {
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
                break;
            }

            if (linux_updater_start_update() != 0)
                ret = CO_SDO_AB_GENERAL;

            break;

        case 7 : // emergency stop update

            if(ODF_arg->reading == true) {
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
                break;
            }

            if (linux_updater_stop_update() == false)
                ret = CO_SDO_AB_GENERAL;

            break;

        case 8 : // reset linux updater

            if(ODF_arg->reading == true)
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
            else {
                if (linux_updater_reset() == false)
                    ret = CO_SDO_AB_GENERAL;
            }

            break;

        case 9 : // get apt update output as a file

            if(ODF_arg->reading == true)
                ret = CO_SDO_AB_WRITEONLY; // can't read parameters, write only
            else {
                if (get_apt_list_output() == false)
                    ret = CO_SDO_AB_GENERAL;
            }

            break;

        default :
            ret = CO_SDO_AB_SUB_UNKNOWN;
    }

    ODF_arg->lastSegment = true;
    return ret;
}


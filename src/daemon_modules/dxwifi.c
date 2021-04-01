/**
 * Module for interfacing with the OreSat DxWiFi daemon over D-Bus.
 *
 * @file        dxwifi.c
 * @ingroup     daemon_modules
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "globals.h"
#include "log_message.h"
#include "olm_app.h"
#include "utility.h"
#include "dxwifi.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <systemd/sd-bus.h>

#define MODULE_NAME         "DxWiFi"
#define SERVICE_FILE        "oresat-dxwifi-txd.service"

void
dxwifi_app(olm_app_t *app) {
    MALLOC_STRNCPY_OR_GOTO(app->name, MODULE_NAME, dxwifi_app_error);
    MALLOC_STRNCPY_OR_GOTO(app->service_file, SERVICE_FILE, dxwifi_app_error);

    return;

dxwifi_app_error:

    OLM_APP_FREE(app);
    return;
}

/**
 * OreSat Live DxWiFi daemon app
 *
 * @file        dxwifi_app.c
 * @ingroup     apps
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "globals.h"
#include "log_message.h"
#include "olm_app.h"
#include "utility.h"
#include "template_app.h"
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <systemd/sd-bus.h>

/** App's name */
#define APP_NAME            "DxWiFi"
/** The systemd service name for the app's daemon */
#define SERVICE_FILE        "oresat-dxwifi-txd.service"

void
dxwifi_app(olm_app_t *app) {
    MALLOC_STRNCPY_OR_GOTO(app->name, APP_NAME, dxwifi_app_error);
    MALLOC_STRNCPY_OR_GOTO(app->service_file, SERVICE_FILE, dxwifi_app_error);

    return;

dxwifi_app_error:

    OLM_APP_FREE(app);
    return;
}

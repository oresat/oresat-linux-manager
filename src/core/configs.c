/**
 * OLM configs.
 *
 * @file        configs.c
 * @ingroup     configs
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for apps running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#define _GNU_SOURCE
#include "configs.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define CONFIG_FILE     "/etc/oresat-linux-manager.conf"

#define NODE_SECTION    "[Node]"
#define NODE_ID_KEY     "ID="
#define BIT_RATE_KEY    "BitRate="

int
read_config_file(olm_configs_t *configs) {
    char *end, *line = NULL;
    size_t len = 0;
    ssize_t read;
    char section[20];
    FILE *fp;

    if (configs == NULL)
        return -1;

    if ((fp = fopen(CONFIG_FILE, "r")) == NULL) {
        log_printf(LOG_INFO, "Config file "CONFIG_FILE" not found\n");
        return -1;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == '#' || line[0] == '\n')
            continue;

        // new section
        if (line[0] == '[') {
            if (strncmp(NODE_SECTION, line, strlen(NODE_SECTION)) == 0)
                strncpy(section, NODE_SECTION, strlen(NODE_SECTION)+1);

            continue;
        }

        if (strncmp(NODE_SECTION, section, strlen(NODE_SECTION)) == 0) {
            if (strncmp(NODE_ID_KEY, line, strlen(NODE_ID_KEY)) == 0)
                configs->node_id = (uint8_t)strtoul(&line[strlen(NODE_ID_KEY)], &end, 0);
            else if (strncmp(BIT_RATE_KEY, line, strlen(BIT_RATE_KEY)) == 0)
                configs->bit_rate = (uint16_t)strtoul(&line[strlen(BIT_RATE_KEY)], &end, 0);
        }
    }

    // validate value
    if (configs->node_id == 0 || configs->node_id > 0x7F) {
        configs->node_id = NODE_ID_DEFAULT;
        log_printf(LOG_ERR, "Invalid node id in "CONFIG_FILE"\n");
    }
    if (configs->bit_rate > 1000) {
        configs->bit_rate = BIT_RATE_DEFAULT;
        log_printf(LOG_ERR, "Invalid bit rate in "CONFIG_FILE"\n");
    }

    free(line);
    return 1;
}

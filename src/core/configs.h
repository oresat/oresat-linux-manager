/**
 * OLM configs.
 *
 * @file        configs.h
 * @ingroup     configs
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for apps running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#ifndef OLM_CONFIGS_H
#define OLM_CONFIGS_H

#include <stdint.h>

/** All OLM's configs from conf file. */
typedef struct {
    /** CANbus interface */
    char interface[100];
    /** Node ID, must be between 0x01 and 0x7F. */
    uint8_t node_id;
    /** CANbus bit rate in kbit/s. Can be 0 for Max is 1000. */
    uint16_t bit_rate;
} olm_configs_t;

#define NODE_ID_DEFAULT     0x7C
#define BIT_RATE_DEFAULT    0

#define OLM_CONFIGS_DEFAULT { \
    .interface = "can0", \
    .node_id = NODE_ID_DEFAULT, \
    .bit_rate = BIT_RATE_DEFAULT, \
}

/**
 * @brief Read configs from conf file.
 *
 * @param configs The @ref olm_configs_t object to fill out.
 *
 * @return 1 on success or negative value on error.
 */
int read_config_file(olm_configs_t *configs);

#endif /* OLM_CONFIGS_H */

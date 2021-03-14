/**
 * Writing files over CAN ODF (Object Dictionary Function).
 *
 * @file        CO_fwrite.h
 * @ingroup     file_transfer
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef CO_FWRITE_H
#define CO_FWRITE_H


#include "CANopen.h"
#include <stdint.h>


/**
 * @defgroup file_transfer File Transfer
 * @{
 *
 * **File Writer OD Record:**
 * | Sub Index | Usage                          | Data Type   | Access    |
 * | :-------- | :----------------------------: | :---------: | :-------: |
 * |     0     | Number of subindex in record   | uint8       | readonly  |
 * |     1     | File name                      | DOMAIN      | writeonly |
 * |     2     | File data                      | DOMAIN      | writeonly |
 * |     2     | Cancel                         | int32       | writeonly |
 *
 * **How file writing works:**
 * The network manager node writes a file name to subindex 1 and then write
 * file data to subindex 2. Must be done as back to back in that order. If 
 * the network manager node need to cancel or reset file transfer, it can 
 * write any int32 number to subindex 3 to clear all buffers and close any
 * files.
 */


/**
 * Setup the file recv.
 * @return 0 on success or negative errno value on error.
 */
int CO_fwrite_setup(void);


/**
 * Make sure file pointer is freed. Also cleans up the file recv.
 * @return 0 on success or negative errno value on error.
 */
int CO_fwrite_end(void);


/**
 * Callback for using inside CO_OD_configure() function for writing files
 * into object dictionary.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t fwrite_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * App request any the file with the key in the filename.
 * @param app_name The app's name, used for logging.
 * @param key Is the unique key in the filename.
 * @param send_dir the path to move the file to after the transfer is complete.
 * @param cb_func A optinal callback function to call when the transfer is
 * complete. Set to NULL, if not wanted. If not NULL, the cb function will be
 * call with the the filename past as a arg.
 * @return 0 on success or negative errno value on error.
 */
int app_fwrite_request(char *app_name, char *key, char *send_dir, void (*cb_func)(const char *));


/** @} */
#endif

/**
 * Reading files over CAN ODF (Object Dictionary Function).
 *
 * @file        CO_fread.h
 * @ingroup     file_transfer
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */


#ifndef CO_FREAD_H
#define CO_FREAD_H


#include "CANopen.h"
#include <stdint.h>


/**
 * @defgroup file_transfer File Transfer
 * @{
 *
 * Object dictionary functions for handlinge file transfers over CAN.
 *
 * There are three object dictionary entries to help with file transfer.
 * One record only deals with writing files to the OLM and two OD records
 * for read from (one for list all readable file available and one for
 * selecting and reading a file).
 *
 * **Readable File List OD Record:**
 * | Sub Index | Usage                          | Data Type   | Access   |
 * | :-------- | :----------------------------: | :---------: | :------: |
 * |     0     | Number of subindex in record   | uint8       | readonly |
 * |     1     | File name 1                    | DOMAIN      | readonly |
 * |    ...    | ...                            | DOMAIN      | readonly |
 * |    127    | File name 127                  | DOMAIN      | readonly |
 *
 * **File Reader OD Record:**
 * | Sub Index | Usage                              | Data Type   | Access    |
 * | :-------- | :--------------------------------: | :---------: | :-------: |
 * |     0     | Number of subindex in record       | uint8       | readonly  |
 * |     1     | Current index in file name array   | uint8       | readwrite |
 * |     2     | File name                          | DOMAIN      | readonly  |
 * |     3     | File data                          | DOMAIN      | readonly  |
 * |     4     | File size                          | uint32      | readonly  |
 * |     5     | Delete file in current index       | boolean     | readwrite |
 * |     6     | Total file available               | uint32      | readonly  |
 * |     7     | Number of files not in file array  | uint32      | readonly  |
 * |     8     | Refresh the file name array        | boolean     | readwrite |
 *
 * **How file reading works:**
 *   - The OLM automatically will fill the Readable File List OD Record on startup.
 *   - The CAN master node can read the file array OD entry and pick which sub-index in the array it wants to read. The master node can choose the file by writing the sub-index of readable file list into File Reader sub-index 1; That will load the file info into sub-indexes 2, 3, and 4 (file name, file data, and file size buffers respectively). Then the master node can read any of those file buffers as it wants to. If the file name or file data is read without loading in a file they will return the value '\0' aka 0x00 (one byte).
 *   - The loaded file can be deleted by reading or writing a value to sub-index 5.
 *   - Sub-index 6 and 7 are just extra useful information for the master node (number of files that could be read and number of file that are not loaded into the Readable File List OD Record).
 *   - Sub-index 8 allows the master node to refresh the Readable File List OD Record. This is useful to add any files that could not be added to the Readable File List OD Record, if the array was full at one point.
 */


/**
 * Configure all application OD functions and setup file transfer cache.
 *
 * @return 0 on success
 */
int CO_fread_setup(void);


/**
 * Clean up all file transfer data, including closing any opened files.
 *
 * @return 0 on success or negative errno on error
 */
int CO_fread_end(void);


/**
 * Callback for using inside CO_OD_configure() function for writing files
 * into object dictionary.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t recv_file_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * Callback for using inside CO_OD_configure() function for reading files
 * from object dictionary.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t fread_array_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * Callback for using inside CO_OD_configure() function for reading files
 * from object dictionary.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t fread_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * Add a file to read over CAN. For apps to use.
 * @return 0 on success or negative errno value on error.
 */
int app_send_file(char *filepath);


/** @} */
#endif

/**
 * File transfer Object Dictionary Function.
 *
 * @file        file_transfer.h
 * @ingroup     file_transfer
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef FILE_TRANSFER_H
#define FILE_TRANSFER_H


#include "CANopen.h"
#include "CO_driver.h"


/**
 * @defgroup file_transfer File Transfer
 * @{
 *
 * Object dictionary functions for handlinge file transfers over CAN.
 *
 * There are three object dictionary entries to help with file transfer.
 * One record only deals with writing files to the CANdaemon and two OD records
 * for read from (one for list all readable file available and one for
 * selecting and reading a file).
 *
 * **File Writer OD Record:**
 * | Sub Index | Usage                          | Data Type   | Access    |
 * | :-------- | :----------------------------: | :---------: | :-------: |
 * |     0     | Number of subindex in record   | uint8       | readonly  |
 * |     1     | File name                      | DOMAIN      | writeonly |
 * |     2     | File data                      | DOMAIN      | writeonly |
 * |     3     | Save file                      | DOMAIN      | writeonly |
 *
 * **How file writing works:**
 * The master node can write data to both file name and file data indexes and then write any 8 bit number to the Save file index to save the file into CANdaemon's received directory.
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
 *   - The CANdaemon automatically will fill the Readable File List OD Record on startup.
 *   - The CAN master node can read the file array OD entry and pick which sub-index in the array it wants to read. The master node can choose the file by writing the sub-index of readable file list into File Reader sub-index 1; That will load the file info into sub-indexes 2, 3, and 4 (file name, file data, and file size buffers respectively). Then the master node can read any of those file buffers as it wants to. If the file name or file data is read without loading in a file they will return the value '\0' aka 0x00 (one byte).
 *   - The loaded file can be deleted by reading or writing a value to sub-index 5.
 *   - Sub-index 6 and 7 are just extra useful information for the master node (number of files that could be read and number of file that are not loaded into the Readable File List OD Record).
 *   - Sub-index 8 allows the master node to refresh the Readable File List OD Record. This is useful to add any files that could not be added to the Readable File List OD Record, if the array was full at one point.
 */


/** The maxium size of file that can be sent */
#define FILE_TRANSFER_MAX_SIZE  1000000
/** The maxium size filepath */
#define FILE_PATH_MAX_LENGTH    200
/** The size of the fileList. Must be <= 127 */
#define SEND_FILE_LIST_SIZE     127


/** Struct for receive files ODF. */
typedef struct {
    /** file name */
    char        fileName[FILE_PATH_MAX_LENGTH];
    /** file data */
    int8_t      fileData[FILE_TRANSFER_MAX_SIZE];
    /** file size */
    uint32_t    fileSize;
    /** flag for triggering the file to be saved */
    bool_t      saveFile;
} received_file_data_t;


/**
 * Struct for sending files ODF.
 *
 * Used to load and access a file that is in sendableFileList
 */
typedef struct {
    /** Index to current file selected in send fileList */
    uint8_t     filePointer;
    /** File name that filePointer points to fileList*/
    char       *fileName;
    /** Absoulte path to file that filePointer points to in fileList */
    char        filePath[FILE_PATH_MAX_LENGTH];
    /** File data of current file that filePointer points to in fileList*/
    int8_t      fileData[FILE_TRANSFER_MAX_SIZE];
    /** Size of file of current file that filePointer points to in fileList*/
    uint32_t    fileSize;
    /** Total number of file availavle */
    uint32_t    filesAvailable;
    /** Number of files that do not fit in the fileList. */
    uint32_t    overflow;
    /** The list of file that can be sent to the CAN master node */
    char        fileList[FILE_PATH_MAX_LENGTH][SEND_FILE_LIST_SIZE];
} send_file_data_t;


/**
 * Configure all application OD functions
 *
 * @return 0 on success
 */
int file_transfer_ODF_setup(void);


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
CO_SDO_abortCode_t send_file_array_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * Callback for using inside CO_OD_configure() function for reading files
 * from object dictionary.
 *
 * @param ODF_arg Current ODF arguemnt for SDO
 *
 * @return SDO abort code
 */
CO_SDO_abortCode_t send_file_ODF(CO_ODF_arg_t *ODF_arg);


/** @} */

/**
 * @ingroup App_Helpers
 * @{
 *
 * Object Dictionary Function for handlinge file transfers over CAN.
 */


/**
 *  Request a file name by add a PCRE2 regex string.
 *
 *  @param app_name is the app name for log messages
 *  @param regex_string is a PCRE2 regex string. used by the recv file ODF
 *  to check if the regex will match.
 *  #param path_to_send is where the file will be move to if ODF match the
 *  file name with regex string.
 *  @param Optional. Set to NULL if not wanted. Function be called if
 *  regex matches.
 *
 *  @return 1 on success, 0 on failure
 */
int app_add_request_recv_file(
        char *app_name,
        char *regex_string,
        char *path_to_send,
        int (*recv_file_callback)(char *));


/**
 * Add file to object dictionary that can be read by a master CAN node.
 * Ment to be used by other part of the CANdaemon (from the app).
 * An example would be giving the master CAN node a captured image.
 *
 * @return 0 on success.
 */
int app_send_file(const char* filePath);


/** @} */
#endif

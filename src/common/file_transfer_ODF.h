/**
 * File transfer Object Dictionary Function.
 *
 * @file        file_transfer_ODF.c
 * @ingroup     file_transfer_ODF
 *
 * This file is part of CANdaemon, a common can interface program for daemons
 * running on OreSat Linux board.
 * Project home page is <https://github.com/oresat/oresat-linux-candaemon>.
 */


#ifndef FILE_TRANSFER_ODF_H
#define FILE_TRANSFER_ODF_H


#include "CANopen.h"
#include "CO_driver.h"


/**
 * @defgroup candaemon_general CANdaemon general
 *
 * Non-app related object dictionary functions
 */


/**
 * @ingroup candaemon_general
 * @defgroup file_transfer_ODF File Transfer ODF
 * @{
 *
 * Object dictionary functions for handlinge file transfers over CAN.
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
 */
int file_transfer_ODF_setup(void);


/**
 * Callback for using inside CO_OD_configure() function for writing files
 * into object dictionary.
 */
CO_SDO_abortCode_t recv_file_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * Callback for using inside CO_OD_configure() function for reading files
 * from object dictionary.
 */
CO_SDO_abortCode_t send_file_array_ODF(CO_ODF_arg_t *ODF_arg);


/**
 * Callback for using inside CO_OD_configure() function for reading files
 * from object dictionary.
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

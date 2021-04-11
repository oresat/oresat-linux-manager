// clang-format off
/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode v1 to v2

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-123-g6c02323

    https://github.com/CANopenNode/CANopenNode
    https://github.com/robincornelius/libedssharp

    DON'T EDIT THIS FILE MANUALLY !!!!
*******************************************************************************/
#ifndef CO_OD_H_
#define CO_OD_H_

/*******************************************************************************
   CANopen DATA TYPES
*******************************************************************************/
   typedef bool_t       BOOLEAN;
   typedef uint8_t      UNSIGNED8;
   typedef uint16_t     UNSIGNED16;
   typedef uint32_t     UNSIGNED32;
   typedef uint64_t     UNSIGNED64;
   typedef int8_t       INTEGER8;
   typedef int16_t      INTEGER16;
   typedef int32_t      INTEGER32;
   typedef int64_t      INTEGER64;
   typedef float32_t    REAL32;
   typedef float64_t    REAL64;
   typedef char_t       VISIBLE_STRING;
   typedef oChar_t      OCTET_STRING;

   #ifdef DOMAIN
   #undef DOMAIN
   #endif

   typedef domain_t     DOMAIN;


/*******************************************************************************
   FILE INFO:
      FileName:     star_tracker.xdd
      FileVersion:  1
      CreationTime: 1:57PM
      CreationDate: 03-09-2021
      CreatedBy:    Ryan Medick
*******************************************************************************/


/*******************************************************************************
   DEVICE INFO:
      VendorName:     Portland State Aerospace Society
      VendorNumber:   0
      ProductName:    OreSat Star Tracker
      ProductNumber:  0
*******************************************************************************/


/*******************************************************************************
   FEATURES
*******************************************************************************/
  #define CO_NO_SYNC                     1   //Associated objects: 1005-1007
  #define CO_NO_EMERGENCY                1   //Associated objects: 1014, 1015
  #define CO_NO_TIME                     0   //Associated objects: 1012, 1013
  #define CO_NO_SDO_SERVER               1   //Associated objects: 1200-127F
  #define CO_NO_SDO_CLIENT               0   //Associated objects: 1280-12FF
  #define CO_NO_GFC                      0   //Associated objects: 1300
  #define CO_NO_SRDO                     0   //Associated objects: 1301-1341, 1381-13C0
  #define CO_NO_LSS_SERVER               0   //LSS Slave
  #define CO_NO_LSS_CLIENT               0   //LSS Master
  #define CO_NO_RPDO                     4   //Associated objects: 14xx, 16xx
  #define CO_NO_TPDO                     4   //Associated objects: 18xx, 1Axx
  #define CO_NO_NMT_MASTER               0
  #define CO_NO_TRACE                    0


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             53


/*******************************************************************************
   TYPE DEFINITIONS FOR RECORDS
*******************************************************************************/
/*1018      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     vendorID;
               UNSIGNED32     productCode;
               UNSIGNED32     revisionNumber;
               UNSIGNED32     serialNumber;
               }              OD_identity_t;
/*1023      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               DOMAIN         command;
               UNSIGNED8      status;
               DOMAIN         reply;
               }              OD_OSCommand_t;
/*1025      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               DOMAIN         command;
               UNSIGNED8      status;
               DOMAIN         reply;
               }              OD_OSDebuggerInterface_t;
/*1200      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               UNSIGNED8      nodeIDOfTheSDOClient;
               }              OD_SDOServerParameter_t;
/*1280      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               UNSIGNED8      nodeIDOfTheSDOServer;
               }              OD_SDOClientParameter_t;
/*1400      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     COB_IDUsedByRPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     eventTimer;
               }              OD_RPDOCommunicationParameter_t;
/*1600      */ typedef struct {
               UNSIGNED8      numberOfMappedApplicationObjectsInPDO;
               UNSIGNED32     mappingObject1;
               UNSIGNED32     mappingObject2;
               UNSIGNED32     mappingObject3;
               UNSIGNED32     mappingObject4;
               UNSIGNED32     mappingObject5;
               UNSIGNED32     mappingObject6;
               UNSIGNED32     mappingObject7;
               UNSIGNED32     mappingObject8;
               }              OD_RPDOMappingParameter_t;
/*1800      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     COB_IDUsedByTPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     inhibitTime;
               UNSIGNED8      compatibilityEntry;
               UNSIGNED16     eventTimer;
               UNSIGNED8      SYNCStartValue;
               }              OD_TPDOCommunicationParameter_t;
/*1A00      */ typedef struct {
               UNSIGNED8      numberOfMappedApplicationObjectsInPDO;
               UNSIGNED32     mappingObject1;
               UNSIGNED32     mappingObject2;
               UNSIGNED32     mappingObject3;
               UNSIGNED32     mappingObject4;
               UNSIGNED32     mappingObject5;
               UNSIGNED32     mappingObject6;
               UNSIGNED32     mappingObject7;
               UNSIGNED32     mappingObject8;
               }              OD_TPDOMappingParameter_t;
/*2000      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      bdefault;
               UNSIGNED8      ttoggle;
               UNSIGNED8      ntoggle;
               UNSIGNED8      ctoggle;
               }              OD_BUSManagement_t;
/*3000      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               DOMAIN         rebootBoard;
               DOMAIN         poweroffBoard;
               BOOLEAN        quit;
               BOOLEAN        CPUFrequency;
               }              OD_OLMControl_t;
/*3001      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               DOMAIN         OSName;
               DOMAIN         OSDistro;
               DOMAIN         OSKernelVersion;
               DOMAIN         hostname;
               UNSIGNED32     uptime;
               UNSIGNED8      numberOfCPUs;
               DOMAIN         CPUArchitecture;
               UNSIGNED8      CPUGovernor;
               UNSIGNED16     CPUFrequency;
               UNSIGNED8      numberOfRemoteprocs;
               UNSIGNED8      remoteprocXSelector;
               DOMAIN         remoteprocXName;
               DOMAIN         remoteprocXState;
               UNSIGNED32     loadAverage1min;
               UNSIGNED32     loadAverage5min;
               UNSIGNED32     loadAverage15min;
               UNSIGNED32     ramTotal;
               UNSIGNED32     ramFree;
               UNSIGNED32     ramShared;
               UNSIGNED32     ramBuffered;
               UNSIGNED8      ramPercent;
               UNSIGNED32     swapTotal;
               UNSIGNED32     swapFree;
               UNSIGNED8      swapPercent;
               UNSIGNED32     procs;
               UNSIGNED32     rootParitionTotal;
               UNSIGNED32     rootParitionFree;
               UNSIGNED8      rootParitionPercent;
               }              OD_systemInfo_t;
/*3002      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      freadCacheLen;
               UNSIGNED8      fwriteCacheLen;
               UNSIGNED8      cacheSelector;
               DOMAIN         filter;
               UNSIGNED32     cacheLen;
               UNSIGNED32     iterator;
               DOMAIN         fileName;
               UNSIGNED32     fileSize;
               DOMAIN         deleteFile;
               }              OD_fileCaches_t;
/*3003      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               DOMAIN         fileName;
               DOMAIN         fileData;
               DOMAIN         reset;
               DOMAIN         deleteFile;
               }              OD_fread_t;
/*3004      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               DOMAIN         fileName;
               DOMAIN         fileData;
               DOMAIN         reset;
               }              OD_fwrite_t;
/*3005      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      totalApps;
               UNSIGNED8      activeApps;
               UNSIGNED8      failedApps;
               UNSIGNED8      selectApp;
               DOMAIN         appName;
               UNSIGNED8      daemonState;
               }              OD_appManager_t;
/*3100      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      status;
               UNSIGNED8      updatesAvailable;
               DOMAIN         listUpdates;
               BOOLEAN        update;
               BOOLEAN        makeStatusFile;
               }              OD_updater_t;
/*6001      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               REAL32         rightAscension;
               REAL32         declination;
               REAL32         roll;
               UNSIGNED32     timestamp;
               }              OD_orienation_t;

/*******************************************************************************
   TYPE DEFINITIONS FOR OBJECT DICTIONARY INDEXES

   some of those are redundant with CO_SDO.h CO_ObjDicId_t <Common CiA301 object
   dictionary entries>
*******************************************************************************/
/*1000 */
        #define OD_1000_deviceType                                  0x1000

/*1001 */
        #define OD_1001_errorRegister                               0x1001

/*1002 */
        #define OD_1002_manufacturerStatusRegister                  0x1002

/*1003 */
        #define OD_1003_preDefinedErrorField                        0x1003

        #define OD_1003_0_preDefinedErrorField_maxSubIndex          0
        #define OD_1003_1_preDefinedErrorField_standardErrorField   1
        #define OD_1003_2_preDefinedErrorField_standardErrorField   2
        #define OD_1003_3_preDefinedErrorField_standardErrorField   3
        #define OD_1003_4_preDefinedErrorField_standardErrorField   4
        #define OD_1003_5_preDefinedErrorField_standardErrorField   5
        #define OD_1003_6_preDefinedErrorField_standardErrorField   6
        #define OD_1003_7_preDefinedErrorField_standardErrorField   7
        #define OD_1003_8_preDefinedErrorField_standardErrorField   8

/*1005 */
        #define OD_1005_COB_ID_SYNCMessage                          0x1005

/*1006 */
        #define OD_1006_communicationCyclePeriod                    0x1006

/*1007 */
        #define OD_1007_synchronousWindowLength                     0x1007

/*1008 */
        #define OD_1008_manufacturerDeviceName                      0x1008

/*1009 */
        #define OD_1009_manufacturerHardwareVersion                 0x1009

/*100A */
        #define OD_100A_manufacturerSoftwareVersion                 0x100A

/*1010 */
        #define OD_1010_storeParameters                             0x1010

        #define OD_1010_0_storeParameters_maxSubIndex               0
        #define OD_1010_1_storeParameters_saveAllParameters         1
        #define OD_1010_2_storeParameters_saveCommunicationParameters 2
        #define OD_1010_3_storeParameters_saveApplicationParameters 3
        #define OD_1010_4_storeParameters_saveManufacturerDefinedParameters 4

/*1011 */
        #define OD_1011_restoreDefaultParameters                    0x1011

        #define OD_1011_0_restoreDefaultParameters_maxSubIndex      0
        #define OD_1011_1_restoreDefaultParameters_restoreAllDefaultParameters 1
        #define OD_1011_2_restoreDefaultParameters_restoreCommunicationDefaultParameters 2
        #define OD_1011_3_restoreDefaultParameters_restoreApplicationDefaultParameters 3
        #define OD_1011_4_restoreDefaultParameters_restoreManufacturerDefinedDefaultParameters 4

/*1014 */
        #define OD_1014_COB_ID_EMCY                                 0x1014

/*1015 */
        #define OD_1015_inhibitTimeEMCY                             0x1015

/*1016 */
        #define OD_1016_consumerHeartbeatTime                       0x1016

        #define OD_1016_0_consumerHeartbeatTime_maxSubIndex         0
        #define OD_1016_1_consumerHeartbeatTime_consumerHeartbeatTime 1
        #define OD_1016_2_consumerHeartbeatTime_consumerHeartbeatTime 2
        #define OD_1016_3_consumerHeartbeatTime_consumerHeartbeatTime 3
        #define OD_1016_4_consumerHeartbeatTime_consumerHeartbeatTime 4
        #define OD_1016_5_consumerHeartbeatTime_consumerHeartbeatTime 5
        #define OD_1016_6_consumerHeartbeatTime_consumerHeartbeatTime 6
        #define OD_1016_7_consumerHeartbeatTime_consumerHeartbeatTime 7
        #define OD_1016_8_consumerHeartbeatTime_consumerHeartbeatTime 8

/*1017 */
        #define OD_1017_producerHeartbeatTime                       0x1017

/*1018 */
        #define OD_1018_identity                                    0x1018

        #define OD_1018_0_identity_maxSubIndex                      0
        #define OD_1018_1_identity_vendorID                         1
        #define OD_1018_2_identity_productCode                      2
        #define OD_1018_3_identity_revisionNumber                   3
        #define OD_1018_4_identity_serialNumber                     4

/*1019 */
        #define OD_1019_synchronousCounterOverflowValue             0x1019

/*1023 */
        #define OD_1023_OSCommand                                   0x1023

        #define OD_1023_0_OSCommand_maxSubIndex                     0
        #define OD_1023_1_OSCommand_command                         1
        #define OD_1023_2_OSCommand_status                          2
        #define OD_1023_3_OSCommand_reply                           3

/*1029 */
        #define OD_1029_errorBehavior                               0x1029

        #define OD_1029_0_errorBehavior_maxSubIndex                 0
        #define OD_1029_1_errorBehavior_communicationError          1
        #define OD_1029_2_errorBehavior_profileOrManufacturerSpecificError 2

/*1200 */
        #define OD_1200_SDOServerParameter                          0x1200

        #define OD_1200_0_SDOServerParameter_maxSubIndex            0
        #define OD_1200_1_SDOServerParameter_COB_IDClientToServer   1
        #define OD_1200_2_SDOServerParameter_COB_IDServerToClient   2
        #define OD_1200_3_SDOServerParameter_nodeIDOfTheSDOClient   3

/*1400 */
        #define OD_1400_RPDOCommunicationParameter                  0x1400

        #define OD_1400_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1400_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1400_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1400_5_RPDOCommunicationParameter_eventTimer     5

/*1401 */
        #define OD_1401_RPDOCommunicationParameter                  0x1401

        #define OD_1401_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1401_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1401_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1401_5_RPDOCommunicationParameter_eventTimer     5

/*1402 */
        #define OD_1402_RPDOCommunicationParameter                  0x1402

        #define OD_1402_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1402_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1402_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1402_5_RPDOCommunicationParameter_eventTimer     5

/*1403 */
        #define OD_1403_RPDOCommunicationParameter                  0x1403

        #define OD_1403_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1403_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1403_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1403_5_RPDOCommunicationParameter_eventTimer     5

/*1600 */
        #define OD_1600_RPDOMappingParameter                        0x1600

        #define OD_1600_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1600_1_RPDOMappingParameter_mappingObject1       1
        #define OD_1600_2_RPDOMappingParameter_mappingObject2       2
        #define OD_1600_3_RPDOMappingParameter_mappingObject3       3
        #define OD_1600_4_RPDOMappingParameter_mappingObject4       4
        #define OD_1600_5_RPDOMappingParameter_mappingObject5       5
        #define OD_1600_6_RPDOMappingParameter_mappingObject6       6
        #define OD_1600_7_RPDOMappingParameter_mappingObject7       7
        #define OD_1600_8_RPDOMappingParameter_mappingObject8       8

/*1601 */
        #define OD_1601_RPDOMappingParameter                        0x1601

        #define OD_1601_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1601_1_RPDOMappingParameter_mappingObject1       1
        #define OD_1601_2_RPDOMappingParameter_mappingObject2       2
        #define OD_1601_3_RPDOMappingParameter_mappingObject3       3
        #define OD_1601_4_RPDOMappingParameter_mappingObject4       4
        #define OD_1601_5_RPDOMappingParameter_mappingObject5       5
        #define OD_1601_6_RPDOMappingParameter_mappingObject6       6
        #define OD_1601_7_RPDOMappingParameter_mappingObject7       7
        #define OD_1601_8_RPDOMappingParameter_mappingObject8       8

/*1602 */
        #define OD_1602_RPDOMappingParameter                        0x1602

        #define OD_1602_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1602_1_RPDOMappingParameter_mappingObject1       1
        #define OD_1602_2_RPDOMappingParameter_mappingObject2       2
        #define OD_1602_3_RPDOMappingParameter_mappingObject3       3
        #define OD_1602_4_RPDOMappingParameter_mappingObject4       4
        #define OD_1602_5_RPDOMappingParameter_mappingObject5       5
        #define OD_1602_6_RPDOMappingParameter_mappingObject6       6
        #define OD_1602_7_RPDOMappingParameter_mappingObject7       7
        #define OD_1602_8_RPDOMappingParameter_mappingObject8       8

/*1603 */
        #define OD_1603_RPDOMappingParameter                        0x1603

        #define OD_1603_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1603_1_RPDOMappingParameter_mappingObject1       1
        #define OD_1603_2_RPDOMappingParameter_mappingObject2       2
        #define OD_1603_3_RPDOMappingParameter_mappingObject3       3
        #define OD_1603_4_RPDOMappingParameter_mappingObject4       4
        #define OD_1603_5_RPDOMappingParameter_mappingObject5       5
        #define OD_1603_6_RPDOMappingParameter_mappingObject6       6
        #define OD_1603_7_RPDOMappingParameter_mappingObject7       7
        #define OD_1603_8_RPDOMappingParameter_mappingObject8       8

/*1800 */
        #define OD_1800_TPDOCommunicationParameter                  0x1800

        #define OD_1800_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1800_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1800_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1800_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1800_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1800_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1800_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1801 */
        #define OD_1801_TPDOCommunicationParameter                  0x1801

        #define OD_1801_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1801_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1801_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1801_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1801_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1801_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1801_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1802 */
        #define OD_1802_TPDOCommunicationParameter                  0x1802

        #define OD_1802_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1802_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1802_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1802_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1802_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1802_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1802_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1803 */
        #define OD_1803_TPDOCommunicationParameter                  0x1803

        #define OD_1803_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1803_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1803_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1803_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1803_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1803_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1803_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1A00 */
        #define OD_1A00_TPDOMappingParameter                        0x1A00

        #define OD_1A00_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A00_1_TPDOMappingParameter_mappingObject1       1
        #define OD_1A00_2_TPDOMappingParameter_mappingObject2       2
        #define OD_1A00_3_TPDOMappingParameter_mappingObject3       3
        #define OD_1A00_4_TPDOMappingParameter_mappingObject4       4
        #define OD_1A00_5_TPDOMappingParameter_mappingObject5       5
        #define OD_1A00_6_TPDOMappingParameter_mappingObject6       6
        #define OD_1A00_7_TPDOMappingParameter_mappingObject7       7
        #define OD_1A00_8_TPDOMappingParameter_mappingObject8       8

/*1A01 */
        #define OD_1A01_TPDOMappingParameter                        0x1A01

        #define OD_1A01_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A01_1_TPDOMappingParameter_mappingObject1       1
        #define OD_1A01_2_TPDOMappingParameter_mappingObject2       2
        #define OD_1A01_3_TPDOMappingParameter_mappingObject3       3
        #define OD_1A01_4_TPDOMappingParameter_mappingObject4       4
        #define OD_1A01_5_TPDOMappingParameter_mappingObject5       5
        #define OD_1A01_6_TPDOMappingParameter_mappingObject6       6
        #define OD_1A01_7_TPDOMappingParameter_mappingObject7       7
        #define OD_1A01_8_TPDOMappingParameter_mappingObject8       8

/*1A02 */
        #define OD_1A02_TPDOMappingParameter                        0x1A02

        #define OD_1A02_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A02_1_TPDOMappingParameter_mappingObject1       1
        #define OD_1A02_2_TPDOMappingParameter_mappingObject2       2
        #define OD_1A02_3_TPDOMappingParameter_mappingObject3       3
        #define OD_1A02_4_TPDOMappingParameter_mappingObject4       4
        #define OD_1A02_5_TPDOMappingParameter_mappingObject5       5
        #define OD_1A02_6_TPDOMappingParameter_mappingObject6       6
        #define OD_1A02_7_TPDOMappingParameter_mappingObject7       7
        #define OD_1A02_8_TPDOMappingParameter_mappingObject8       8

/*1A03 */
        #define OD_1A03_TPDOMappingParameter                        0x1A03

        #define OD_1A03_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A03_1_TPDOMappingParameter_mappingObject1       1
        #define OD_1A03_2_TPDOMappingParameter_mappingObject2       2
        #define OD_1A03_3_TPDOMappingParameter_mappingObject3       3
        #define OD_1A03_4_TPDOMappingParameter_mappingObject4       4
        #define OD_1A03_5_TPDOMappingParameter_mappingObject5       5
        #define OD_1A03_6_TPDOMappingParameter_mappingObject6       6
        #define OD_1A03_7_TPDOMappingParameter_mappingObject7       7
        #define OD_1A03_8_TPDOMappingParameter_mappingObject8       8

/*1F80 */
        #define OD_1F80_NMTStartup                                  0x1F80

/*2000 */
        #define OD_2000_BUSManagement                               0x2000

        #define OD_2000_0_BUSManagement_maxSubIndex                 0
        #define OD_2000_1_BUSManagement_bdefault                    1
        #define OD_2000_2_BUSManagement_ttoggle                     2
        #define OD_2000_3_BUSManagement_ntoggle                     3
        #define OD_2000_4_BUSManagement_ctoggle                     4

/*2010 */
        #define OD_2010_SCET                                        0x2010

/*2011 */
        #define OD_2011_UTC                                         0x2011

/*2100 */
        #define OD_2100_errorStatusBits                             0x2100

/*3000 */
        #define OD_3000_OLMControl                                  0x3000

        #define OD_3000_0_OLMControl_maxSubIndex                    0
        #define OD_3000_1_OLMControl_rebootBoard                    1
        #define OD_3000_2_OLMControl_poweroffBoard                  2
        #define OD_3000_3_OLMControl_quit                           3
        #define OD_3000_4_OLMControl_CPUFrequency                   4

/*3001 */
        #define OD_3001_systemInfo                                  0x3001

        #define OD_3001_0_systemInfo_maxSubIndex                    0
        #define OD_3001_1_systemInfo_OSName                         1
        #define OD_3001_2_systemInfo_OSDistro                       2
        #define OD_3001_3_systemInfo_OSKernelVersion                3
        #define OD_3001_4_systemInfo_hostname                       4
        #define OD_3001_5_systemInfo_uptime                         5
        #define OD_3001_6_systemInfo_numberOfCPUs                   6
        #define OD_3001_7_systemInfo_CPUArchitecture                7
        #define OD_3001_8_systemInfo_CPUGovernor                    8
        #define OD_3001_9_systemInfo_CPUFrequency                   9
        #define OD_3001_10_systemInfo_numberOfRemoteprocs           10
        #define OD_3001_11_systemInfo_remoteprocXSelector           11
        #define OD_3001_12_systemInfo_remoteprocXName               12
        #define OD_3001_13_systemInfo_remoteprocXState              13
        #define OD_3001_14_systemInfo_loadAverage1min               14
        #define OD_3001_15_systemInfo_loadAverage5min               15
        #define OD_3001_16_systemInfo_loadAverage15min              16
        #define OD_3001_17_systemInfo_ramTotal                      17
        #define OD_3001_18_systemInfo_ramFree                       18
        #define OD_3001_19_systemInfo_ramShared                     19
        #define OD_3001_20_systemInfo_ramBuffered                   20
        #define OD_3001_21_systemInfo_ramPercent                    21
        #define OD_3001_22_systemInfo_swapTotal                     22
        #define OD_3001_23_systemInfo_swapFree                      23
        #define OD_3001_24_systemInfo_swapPercent                   24
        #define OD_3001_25_systemInfo_procs                         25
        #define OD_3001_26_systemInfo_rootParitionTotal             26
        #define OD_3001_27_systemInfo_rootParitionFree              27
        #define OD_3001_28_systemInfo_rootParitionPercent           28

/*3002 */
        #define OD_3002_fileCaches                                  0x3002

        #define OD_3002_0_fileCaches_maxSubIndex                    0
        #define OD_3002_1_fileCaches_freadCacheLen                  1
        #define OD_3002_2_fileCaches_fwriteCacheLen                 2
        #define OD_3002_3_fileCaches_cacheSelector                  3
        #define OD_3002_4_fileCaches_filter                         4
        #define OD_3002_5_fileCaches_cacheLen                       5
        #define OD_3002_6_fileCaches_iterator                       6
        #define OD_3002_7_fileCaches_fileName                       7
        #define OD_3002_8_fileCaches_fileSize                       8
        #define OD_3002_9_fileCaches_deleteFile                     9

/*3003 */
        #define OD_3003_fread                                       0x3003

        #define OD_3003_0_fread_maxSubIndex                         0
        #define OD_3003_1_fread_fileName                            1
        #define OD_3003_2_fread_fileData                            2
        #define OD_3003_3_fread_reset                               3
        #define OD_3003_4_fread_deleteFile                          4

/*3004 */
        #define OD_3004_fwrite                                      0x3004

        #define OD_3004_0_fwrite_maxSubIndex                        0
        #define OD_3004_1_fwrite_fileName                           1
        #define OD_3004_2_fwrite_fileData                           2
        #define OD_3004_3_fwrite_reset                              3

/*3005 */
        #define OD_3005_appManager                                  0x3005

        #define OD_3005_0_appManager_maxSubIndex                    0
        #define OD_3005_1_appManager_totalApps                      1
        #define OD_3005_2_appManager_activeApps                     2
        #define OD_3005_3_appManager_failedApps                     3
        #define OD_3005_4_appManager_selectApp                      4
        #define OD_3005_5_appManager_appName                        5
        #define OD_3005_6_appManager_daemonState                    6

/*3006 */
        #define OD_3006_getLog                                      0x3006

/*3100 */
        #define OD_3100_updater                                     0x3100

        #define OD_3100_0_updater_maxSubIndex                       0
        #define OD_3100_1_updater_status                            1
        #define OD_3100_2_updater_updatesAvailable                  2
        #define OD_3100_3_updater_listUpdates                       3
        #define OD_3100_4_updater_update                            4
        #define OD_3100_5_updater_makeStatusFile                    5

/*6000 */
        #define OD_6000_starTrackerStatus                           0x6000

/*6001 */
        #define OD_6001_orienation                                  0x6001

        #define OD_6001_0_orienation_maxSubIndex                    0
        #define OD_6001_1_orienation_rightAscension                 1
        #define OD_6001_2_orienation_declination                    2
        #define OD_6001_3_orienation_roll                           3
        #define OD_6001_4_orienation_timestamp                      4

/*6002 */
        #define OD_6002_capture                                     0x6002

/*******************************************************************************
   STRUCTURES FOR VARIABLES IN DIFFERENT MEMORY LOCATIONS
*******************************************************************************/
#define  CO_OD_FIRST_LAST_WORD     0x55 //Any value from 0x01 to 0xFE. If changed, EEPROM will be reinitialized.

/***** Structure for RAM variables ********************************************/
struct sCO_OD_RAM{
               UNSIGNED32     FirstWord;

/*1001      */ UNSIGNED8      errorRegister;
/*1002      */ UNSIGNED32     manufacturerStatusRegister;
/*1003      */ UNSIGNED32      preDefinedErrorField[8];
/*1010      */ UNSIGNED32      storeParameters[4];
/*1011      */ UNSIGNED32      restoreDefaultParameters[4];
/*1023      */ OD_OSCommand_t  OSCommand;
/*2010      */ UNSIGNED64     SCET;
/*2011      */ UNSIGNED64     UTC;
/*2100      */ OCTET_STRING   errorStatusBits[10];
/*3000      */ OD_OLMControl_t OLMControl;
/*3001      */ OD_systemInfo_t systemInfo;
/*3002      */ OD_fileCaches_t fileCaches;
/*3003      */ OD_fread_t      fread;
/*3004      */ OD_fwrite_t     fwrite;
/*3005      */ OD_appManager_t appManager;
/*3006      */ UNSIGNED8      getLog;
/*3100      */ OD_updater_t    updater;
/*6000      */ UNSIGNED8      starTrackerStatus;
/*6001      */ OD_orienation_t orienation;
/*6002      */ UNSIGNED8      capture;

               UNSIGNED32     LastWord;
};

/***** Structure for ROM variables ********************************************/
struct sCO_OD_ROM{
               UNSIGNED32     FirstWord;

/*1000      */ UNSIGNED32     deviceType;
/*1008      */ VISIBLE_STRING manufacturerDeviceName[11];
/*1009      */ VISIBLE_STRING manufacturerHardwareVersion[3];
/*100A      */ VISIBLE_STRING manufacturerSoftwareVersion[5];
/*1018      */ OD_identity_t   identity;

               UNSIGNED32     LastWord;
};

/***** Structure for EEPROM variables ********************************************/
struct sCO_OD_EEPROM{
               UNSIGNED32     FirstWord;


               UNSIGNED32     LastWord;
};

/***** Structure for PERSIST_COMM variables ********************************************/
struct sCO_OD_PERSIST_COMM{
               UNSIGNED32     FirstWord;

/*1005      */ UNSIGNED32     COB_ID_SYNCMessage;
/*1006      */ UNSIGNED32     communicationCyclePeriod;
/*1007      */ UNSIGNED32     synchronousWindowLength;
/*1014      */ UNSIGNED32     COB_ID_EMCY;
/*1015      */ UNSIGNED16     inhibitTimeEMCY;
/*1016      */ UNSIGNED32      consumerHeartbeatTime[8];
/*1017      */ UNSIGNED16     producerHeartbeatTime;
/*1019      */ UNSIGNED8      synchronousCounterOverflowValue;
/*1029      */ UNSIGNED8       errorBehavior[2];
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[4];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[4];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[4];
/*1A00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[4];
/*1F80      */ UNSIGNED32     NMTStartup;

               UNSIGNED32     LastWord;
};

/***** Structure for PERSIST_MFR variables ********************************************/
struct sCO_OD_PERSIST_MFR{
               UNSIGNED32     FirstWord;

/*2000      */ OD_BUSManagement_t BUSManagement;

               UNSIGNED32     LastWord;
};

/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_ROM CO_OD_ROM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

extern struct sCO_OD_PERSIST_COMM CO_OD_PERSIST_COMM;

extern struct sCO_OD_PERSIST_MFR CO_OD_PERSIST_MFR;

/*******************************************************************************
   ALIASES FOR OBJECT DICTIONARY VARIABLES
*******************************************************************************/
/*1000, Data Type: UNSIGNED32 */
        #define OD_deviceType                                       CO_OD_ROM.deviceType

/*1001, Data Type: UNSIGNED8 */
        #define OD_errorRegister                                    CO_OD_RAM.errorRegister

/*1002, Data Type: UNSIGNED32 */
        #define OD_manufacturerStatusRegister                       CO_OD_RAM.manufacturerStatusRegister

/*1003, Data Type: UNSIGNED32, Array[8] */
        #define OD_preDefinedErrorField                             CO_OD_RAM.preDefinedErrorField
        #define ODL_preDefinedErrorField_arrayLength                8
        #define ODA_preDefinedErrorField_standardErrorField         0

/*1005, Data Type: UNSIGNED32 */
        #define OD_COB_ID_SYNCMessage                               CO_OD_PERSIST_COMM.COB_ID_SYNCMessage

/*1006, Data Type: UNSIGNED32 */
        #define OD_communicationCyclePeriod                         CO_OD_PERSIST_COMM.communicationCyclePeriod

/*1007, Data Type: UNSIGNED32 */
        #define OD_synchronousWindowLength                          CO_OD_PERSIST_COMM.synchronousWindowLength

/*1008, Data Type: VISIBLE_STRING */
        #define OD_manufacturerDeviceName                           CO_OD_ROM.manufacturerDeviceName
        #define ODL_manufacturerDeviceName_stringLength             11

/*1009, Data Type: VISIBLE_STRING */
        #define OD_manufacturerHardwareVersion                      CO_OD_ROM.manufacturerHardwareVersion
        #define ODL_manufacturerHardwareVersion_stringLength        3

/*100A, Data Type: VISIBLE_STRING */
        #define OD_manufacturerSoftwareVersion                      CO_OD_ROM.manufacturerSoftwareVersion
        #define ODL_manufacturerSoftwareVersion_stringLength        5

/*1010, Data Type: UNSIGNED32, Array[4] */
        #define OD_storeParameters                                  CO_OD_RAM.storeParameters
        #define ODL_storeParameters_arrayLength                     4
        #define ODA_storeParameters_saveAllParameters               0
        #define ODA_storeParameters_saveCommunicationParameters     1
        #define ODA_storeParameters_saveApplicationParameters       2
        #define ODA_storeParameters_saveManufacturerDefinedParameters 3

/*1011, Data Type: UNSIGNED32, Array[4] */
        #define OD_restoreDefaultParameters                         CO_OD_RAM.restoreDefaultParameters
        #define ODL_restoreDefaultParameters_arrayLength            4
        #define ODA_restoreDefaultParameters_restoreAllDefaultParameters 0
        #define ODA_restoreDefaultParameters_restoreCommunicationDefaultParameters 1
        #define ODA_restoreDefaultParameters_restoreApplicationDefaultParameters 2
        #define ODA_restoreDefaultParameters_restoreManufacturerDefinedDefaultParameters 3

/*1014, Data Type: UNSIGNED32 */
        #define OD_COB_ID_EMCY                                      CO_OD_PERSIST_COMM.COB_ID_EMCY

/*1015, Data Type: UNSIGNED16 */
        #define OD_inhibitTimeEMCY                                  CO_OD_PERSIST_COMM.inhibitTimeEMCY

/*1016, Data Type: UNSIGNED32, Array[8] */
        #define OD_consumerHeartbeatTime                            CO_OD_PERSIST_COMM.consumerHeartbeatTime
        #define ODL_consumerHeartbeatTime_arrayLength               8
        #define ODA_consumerHeartbeatTime_consumerHeartbeatTime     0

/*1017, Data Type: UNSIGNED16 */
        #define OD_producerHeartbeatTime                            CO_OD_PERSIST_COMM.producerHeartbeatTime

/*1018, Data Type: identity_t */
        #define OD_identity                                         CO_OD_ROM.identity

/*1019, Data Type: UNSIGNED8 */
        #define OD_synchronousCounterOverflowValue                  CO_OD_PERSIST_COMM.synchronousCounterOverflowValue

/*1023, Data Type: OSCommand_t */
        #define OD_OSCommand                                        CO_OD_RAM.OSCommand

/*1029, Data Type: UNSIGNED8, Array[2] */
        #define OD_errorBehavior                                    CO_OD_PERSIST_COMM.errorBehavior
        #define ODL_errorBehavior_arrayLength                       2
        #define ODA_errorBehavior_communicationError                0
        #define ODA_errorBehavior_profileOrManufacturerSpecificError 1

/*1200, Data Type: SDOServerParameter_t */
        #define OD_SDOServerParameter                               CO_OD_PERSIST_COMM.SDOServerParameter

/*1400, Data Type: RPDOCommunicationParameter_t */
        #define OD_RPDOCommunicationParameter                       CO_OD_PERSIST_COMM.RPDOCommunicationParameter

/*1600, Data Type: RPDOMappingParameter_t */
        #define OD_RPDOMappingParameter                             CO_OD_PERSIST_COMM.RPDOMappingParameter

/*1800, Data Type: TPDOCommunicationParameter_t */
        #define OD_TPDOCommunicationParameter                       CO_OD_PERSIST_COMM.TPDOCommunicationParameter

/*1A00, Data Type: TPDOMappingParameter_t */
        #define OD_TPDOMappingParameter                             CO_OD_PERSIST_COMM.TPDOMappingParameter

/*1F80, Data Type: UNSIGNED32 */
        #define OD_NMTStartup                                       CO_OD_PERSIST_COMM.NMTStartup

/*2000, Data Type: BUSManagement_t */
        #define OD_BUSManagement                                    CO_OD_PERSIST_MFR.BUSManagement

/*2010, Data Type: UNSIGNED64 */
        #define OD_SCET                                             CO_OD_RAM.SCET

/*2011, Data Type: UNSIGNED64 */
        #define OD_UTC                                              CO_OD_RAM.UTC

/*2100, Data Type: OCTET_STRING */
        #define OD_errorStatusBits                                  CO_OD_RAM.errorStatusBits
        #define ODL_errorStatusBits_stringLength                    10

/*3000, Data Type: OLMControl_t */
        #define OD_OLMControl                                       CO_OD_RAM.OLMControl

/*3001, Data Type: systemInfo_t */
        #define OD_systemInfo                                       CO_OD_RAM.systemInfo

/*3002, Data Type: fileCaches_t */
        #define OD_fileCaches                                       CO_OD_RAM.fileCaches

/*3003, Data Type: fread_t */
        #define OD_fread                                            CO_OD_RAM.fread

/*3004, Data Type: fwrite_t */
        #define OD_fwrite                                           CO_OD_RAM.fwrite

/*3005, Data Type: appManager_t */
        #define OD_appManager                                       CO_OD_RAM.appManager

/*3006, Data Type: UNSIGNED8 */
        #define OD_getLog                                           CO_OD_RAM.getLog

/*3100, Data Type: updater_t */
        #define OD_updater                                          CO_OD_RAM.updater

/*6000, Data Type: UNSIGNED8 */
        #define OD_starTrackerStatus                                CO_OD_RAM.starTrackerStatus

/*6001, Data Type: orienation_t */
        #define OD_orienation                                       CO_OD_RAM.orienation

/*6002, Data Type: UNSIGNED8 */
        #define OD_capture                                          CO_OD_RAM.capture

#endif
// clang-format on

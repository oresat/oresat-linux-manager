// clang-format off
/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode v1 to v2

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-121-g3349c4d

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
      FileName:     live_OD.xdd
      FileVersion:  0
      CreationTime: 11:32AM
      CreationDate: 11-07-2019
      CreatedBy:    Ryan Medick
*******************************************************************************/


/*******************************************************************************
   DEVICE INFO:
      VendorName:     Portland State Aerospace Society
      VendorNumber:   0
      ProductName:    OreSat Live
      ProductNumber:  0
*******************************************************************************/


/*******************************************************************************
   FEATURES
*******************************************************************************/
  #define CO_NO_SYNC                     1   //Associated objects: 1005-1007
  #define CO_NO_EMERGENCY                1   //Associated objects: 1014, 1015
  #define CO_NO_TIME                     0   //Associated objects: 1012, 1013
  #define CO_NO_SDO_SERVER               1   //Associated objects: 1200-127F
  #define CO_NO_SDO_CLIENT               1   //Associated objects: 1280-12FF
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
   #define CO_OD_NoOfElements             56


/*******************************************************************************
   TYPE DEFINITIONS FOR RECORDS
*******************************************************************************/
/*1018      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     vendorID;
               UNSIGNED32     productCode;
               UNSIGNED32     revisionNumber;
               UNSIGNED32     serialNumber;
               }              OD_identity_t;
/*1200      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               }              OD_SDOServerParameter_t;
/*1280      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               UNSIGNED8      nodeIDOfTheSDOServer;
               }              OD_SDOClientParameter_t;
/*1400      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByRPDO;
               UNSIGNED8      transmissionType;
               }              OD_RPDOCommunicationParameter_t;
/*1600      */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_RPDOMappingParameter_t;
/*1800      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByTPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     inhibitTime;
               UNSIGNED8      compatibilityEntry;
               UNSIGNED16     eventTimer;
               UNSIGNED8      SYNCStartValue;
               }              OD_TPDOCommunicationParameter_t;
/*1A00      */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_TPDOMappingParameter_t;
/*2130      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               VISIBLE_STRING string[1];
               UNSIGNED64     epochTimeBaseMs;
               UNSIGNED32     epochTimeOffsetMs;
               }              OD_time_t;
/*3000      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               DOMAIN         OSName;
               DOMAIN         OSDistro;
               DOMAIN         OSKernelVersion;
               DOMAIN         hostname;
               UNSIGNED32     uptime;
               UNSIGNED8      numberOfCPUs;
               DOMAIN         CPU_Architecture;
               UNSIGNED8      CPUGovernor;
               UNSIGNED16     CPUFrequency;
               UNSIGNED8      numberOfRemoteprocs;
               UNSIGNED8      remoteprocXSelector;
               DOMAIN         remoteprocXName;
               DOMAIN         remoteprocXState;
               UNSIGNED32     loadAverage1mn;
               UNSIGNED32     loadAverage5min;
               UNSIGNED32     loadAverage15min;
               UNSIGNED32     freeRam;
               UNSIGNED32     sharedRam;
               UNSIGNED32     bufferedRam;
               UNSIGNED32     totalSwap;
               UNSIGNED32     freeSwap;
               UNSIGNED32     procs;
               UNSIGNED32     rootParitionTotal;
               UNSIGNED32     rootParitionFree;
               }              OD_boardInfo_t;
/*3001      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               DOMAIN         fileName;
               DOMAIN         fileData;
               DOMAIN         cancel;
               }              OD_writeFile_t;
/*3003      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED8      fileListIndex;
               DOMAIN         filename;
               DOMAIN         fileData;
               UNSIGNED32     fileSize;
               DOMAIN         deleteFile;
               UNSIGNED32     totalFilesAvailable;
               UNSIGNED32     overflow;
               DOMAIN         refreshFileList;
               }              OD_readFileControl_t;
/*3005      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED8      selectApp;
               DOMAIN         appName;
               DOMAIN         daemonServiceName;
               INTEGER32      daemonCurrentState;
               }              OD_daemonManager_t;
/*3006      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               }              OD_syslogReader_t;
/*30F0      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER32      currentState;
               UNSIGNED32     updatesAvailable;
               DOMAIN         currentUpdateFile;
               DOMAIN         errorMessage;
               DOMAIN         addUpdateFile;
               DOMAIN         startUpdate;
               DOMAIN         emergencyStopUpdate;
               DOMAIN         resetUpdater;
               DOMAIN         getAptListOutput;
               }              OD_linuxUpdaterApp_t;

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

/*1011 */
        #define OD_1011_restoreDefaultParameters                    0x1011

        #define OD_1011_0_restoreDefaultParameters_maxSubIndex      0
        #define OD_1011_1_restoreDefaultParameters_restoreAllDefaultParameters 1

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

/*1029 */
        #define OD_1029_errorBehavior                               0x1029

        #define OD_1029_0_errorBehavior_maxSubIndex                 0
        #define OD_1029_1_errorBehavior_communication               1
        #define OD_1029_2_errorBehavior_communicationOther          2
        #define OD_1029_3_errorBehavior_communicationPassive        3
        #define OD_1029_4_errorBehavior_generic                     4
        #define OD_1029_5_errorBehavior_deviceProfile               5
        #define OD_1029_6_errorBehavior_manufacturerSpecific        6

/*1200 */
        #define OD_1200_SDOServerParameter                          0x1200

        #define OD_1200_0_SDOServerParameter_maxSubIndex            0
        #define OD_1200_1_SDOServerParameter_COB_IDClientToServer   1
        #define OD_1200_2_SDOServerParameter_COB_IDServerToClient   2

/*1280 */
        #define OD_1280_SDOClientParameter                          0x1280

        #define OD_1280_0_SDOClientParameter_maxSubIndex            0
        #define OD_1280_1_SDOClientParameter_COB_IDClientToServer   1
        #define OD_1280_2_SDOClientParameter_COB_IDServerToClient   2
        #define OD_1280_3_SDOClientParameter_nodeIDOfTheSDOServer   3

/*1400 */
        #define OD_1400_RPDOCommunicationParameter                  0x1400

        #define OD_1400_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1400_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1400_2_RPDOCommunicationParameter_transmissionType 2

/*1401 */
        #define OD_1401_RPDOCommunicationParameter                  0x1401

        #define OD_1401_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1401_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1401_2_RPDOCommunicationParameter_transmissionType 2

/*1402 */
        #define OD_1402_RPDOCommunicationParameter                  0x1402

        #define OD_1402_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1402_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1402_2_RPDOCommunicationParameter_transmissionType 2

/*1403 */
        #define OD_1403_RPDOCommunicationParameter                  0x1403

        #define OD_1403_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1403_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1403_2_RPDOCommunicationParameter_transmissionType 2

/*1600 */
        #define OD_1600_RPDOMappingParameter                        0x1600

        #define OD_1600_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1600_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1600_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1600_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1600_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1600_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1600_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1600_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1600_8_RPDOMappingParameter_mappedObject8        8

/*1601 */
        #define OD_1601_RPDOMappingParameter                        0x1601

        #define OD_1601_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1601_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1601_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1601_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1601_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1601_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1601_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1601_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1601_8_RPDOMappingParameter_mappedObject8        8

/*1602 */
        #define OD_1602_RPDOMappingParameter                        0x1602

        #define OD_1602_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1602_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1602_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1602_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1602_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1602_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1602_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1602_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1602_8_RPDOMappingParameter_mappedObject8        8

/*1603 */
        #define OD_1603_RPDOMappingParameter                        0x1603

        #define OD_1603_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1603_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1603_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1603_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1603_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1603_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1603_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1603_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1603_8_RPDOMappingParameter_mappedObject8        8

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
        #define OD_1A00_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A00_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A00_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A00_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A00_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A00_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A00_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A00_8_TPDOMappingParameter_mappedObject8        8

/*1A01 */
        #define OD_1A01_TPDOMappingParameter                        0x1A01

        #define OD_1A01_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A01_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A01_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A01_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A01_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A01_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A01_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A01_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A01_8_TPDOMappingParameter_mappedObject8        8

/*1A02 */
        #define OD_1A02_TPDOMappingParameter                        0x1A02

        #define OD_1A02_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A02_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A02_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A02_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A02_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A02_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A02_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A02_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A02_8_TPDOMappingParameter_mappedObject8        8

/*1A03 */
        #define OD_1A03_TPDOMappingParameter                        0x1A03

        #define OD_1A03_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A03_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A03_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A03_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A03_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A03_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A03_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A03_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A03_8_TPDOMappingParameter_mappedObject8        8

/*1F80 */
        #define OD_1F80_NMTStartup                                  0x1F80

/*2100 */
        #define OD_2100_errorStatusBits                             0x2100

/*2101 */
        #define OD_2101_CANNodeID                                   0x2101

/*2102 */
        #define OD_2102_CANBitRate                                  0x2102

/*2103 */
        #define OD_2103_SYNCCounter                                 0x2103

/*2104 */
        #define OD_2104_SYNCTime                                    0x2104

/*2106 */
        #define OD_2106_powerOnCounter                              0x2106

/*2107 */
        #define OD_2107_performance                                 0x2107

        #define OD_2107_0_performance_maxSubIndex                   0
        #define OD_2107_1_performance_cyclesPerSecond               1
        #define OD_2107_2_performance_timerCycleTime                2
        #define OD_2107_3_performance_timerCycleMaxTime             3
        #define OD_2107_4_performance_mainCycleTime                 4
        #define OD_2107_5_performance_mainCycleMaxTime              5

/*2108 */
        #define OD_2108_temperature                                 0x2108

        #define OD_2108_0_temperature_maxSubIndex                   0
        #define OD_2108_1_temperature_mainPCB                       1

/*2109 */
        #define OD_2109_voltage                                     0x2109

        #define OD_2109_0_voltage_maxSubIndex                       0
        #define OD_2109_1_voltage_mainPCBSupply                     1

/*2130 */
        #define OD_2130_time                                        0x2130

        #define OD_2130_0_time_maxSubIndex                          0
        #define OD_2130_1_time_string                               1
        #define OD_2130_2_time_epochTimeBaseMs                      2
        #define OD_2130_3_time_epochTimeOffsetMs                    3

/*3000 */
        #define OD_3000_boardInfo                                   0x3000

        #define OD_3000_0_boardInfo_maxSubIndex                     0
        #define OD_3000_1_boardInfo_OSName                          1
        #define OD_3000_2_boardInfo_OSDistro                        2
        #define OD_3000_3_boardInfo_OSKernelVersion                 3
        #define OD_3000_4_boardInfo_hostname                        4
        #define OD_3000_5_boardInfo_uptime                          5
        #define OD_3000_6_boardInfo_numberOfCPUs                    6
        #define OD_3000_7_boardInfo_CPU_Architecture                7
        #define OD_3000_8_boardInfo_CPUGovernor                     8
        #define OD_3000_9_boardInfo_CPUFrequency                    9
        #define OD_3000_10_boardInfo_numberOfRemoteprocs            10
        #define OD_3000_11_boardInfo_remoteprocXSelector            11
        #define OD_3000_12_boardInfo_remoteprocXName                12
        #define OD_3000_13_boardInfo_remoteprocXState               13
        #define OD_3000_14_boardInfo_loadAverage1mn                 14
        #define OD_3000_15_boardInfo_loadAverage5min                15
        #define OD_3000_16_boardInfo_loadAverage15min               16
        #define OD_3000_17_boardInfo_freeRam                        17
        #define OD_3000_18_boardInfo_sharedRam                      18
        #define OD_3000_19_boardInfo_bufferedRam                    19
        #define OD_3000_20_boardInfo_totalSwap                      20
        #define OD_3000_21_boardInfo_freeSwap                       21
        #define OD_3000_22_boardInfo_procs                          22
        #define OD_3000_23_boardInfo_rootParitionTotal              23
        #define OD_3000_24_boardInfo_rootParitionFree               24

/*3001 */
        #define OD_3001_writeFile                                   0x3001

        #define OD_3001_0_writeFile_maxSubIndex                     0
        #define OD_3001_1_writeFile_fileName                        1
        #define OD_3001_2_writeFile_fileData                        2
        #define OD_3001_3_writeFile_cancel                          3

/*3002 */
        #define OD_3002_readFileList                                0x3002

        #define OD_3002_0_readFileList_maxSubIndex                  0
        #define OD_3002_1_readFileList_                             1
        #define OD_3002_2_readFileList_                             2
        #define OD_3002_3_readFileList_                             3
        #define OD_3002_4_readFileList_                             4
        #define OD_3002_5_readFileList_                             5
        #define OD_3002_6_readFileList_                             6
        #define OD_3002_7_readFileList_                             7
        #define OD_3002_8_readFileList_                             8
        #define OD_3002_9_readFileList_                             9
        #define OD_3002_10_readFileList_                            10
        #define OD_3002_11_readFileList_                            11
        #define OD_3002_12_readFileList_                            12
        #define OD_3002_13_readFileList_                            13
        #define OD_3002_14_readFileList_                            14
        #define OD_3002_15_readFileList_                            15
        #define OD_3002_16_readFileList_                            16
        #define OD_3002_17_readFileList_                            17
        #define OD_3002_18_readFileList_                            18
        #define OD_3002_19_readFileList_                            19
        #define OD_3002_20_readFileList_                            20
        #define OD_3002_21_readFileList_                            21
        #define OD_3002_22_readFileList_                            22
        #define OD_3002_23_readFileList_                            23
        #define OD_3002_24_readFileList_                            24
        #define OD_3002_25_readFileList_                            25
        #define OD_3002_26_readFileList_                            26
        #define OD_3002_27_readFileList_                            27
        #define OD_3002_28_readFileList_                            28
        #define OD_3002_29_readFileList_                            29
        #define OD_3002_30_readFileList_                            30
        #define OD_3002_31_readFileList_                            31
        #define OD_3002_32_readFileList_                            32
        #define OD_3002_33_readFileList_                            33
        #define OD_3002_34_readFileList_                            34
        #define OD_3002_35_readFileList_                            35
        #define OD_3002_36_readFileList_                            36
        #define OD_3002_37_readFileList_                            37
        #define OD_3002_38_readFileList_                            38
        #define OD_3002_39_readFileList_                            39
        #define OD_3002_40_readFileList_                            40
        #define OD_3002_41_readFileList_                            41
        #define OD_3002_42_readFileList_                            42
        #define OD_3002_43_readFileList_                            43
        #define OD_3002_44_readFileList_                            44
        #define OD_3002_45_readFileList_                            45
        #define OD_3002_46_readFileList_                            46
        #define OD_3002_47_readFileList_                            47
        #define OD_3002_48_readFileList_                            48
        #define OD_3002_49_readFileList_                            49
        #define OD_3002_50_readFileList_                            50
        #define OD_3002_51_readFileList_                            51
        #define OD_3002_52_readFileList_                            52
        #define OD_3002_53_readFileList_                            53
        #define OD_3002_54_readFileList_                            54
        #define OD_3002_55_readFileList_                            55
        #define OD_3002_56_readFileList_                            56
        #define OD_3002_57_readFileList_                            57
        #define OD_3002_58_readFileList_                            58
        #define OD_3002_59_readFileList_                            59
        #define OD_3002_60_readFileList_                            60
        #define OD_3002_61_readFileList_                            61
        #define OD_3002_62_readFileList_                            62
        #define OD_3002_63_readFileList_                            63
        #define OD_3002_64_readFileList_                            64
        #define OD_3002_65_readFileList_                            65
        #define OD_3002_66_readFileList_                            66
        #define OD_3002_67_readFileList_                            67
        #define OD_3002_68_readFileList_                            68
        #define OD_3002_69_readFileList_                            69
        #define OD_3002_70_readFileList_                            70
        #define OD_3002_71_readFileList_                            71
        #define OD_3002_72_readFileList_                            72
        #define OD_3002_73_readFileList_                            73
        #define OD_3002_74_readFileList_                            74
        #define OD_3002_75_readFileList_                            75
        #define OD_3002_76_readFileList_                            76
        #define OD_3002_77_readFileList_                            77
        #define OD_3002_78_readFileList_                            78
        #define OD_3002_79_readFileList_                            79
        #define OD_3002_80_readFileList_                            80
        #define OD_3002_81_readFileList_                            81
        #define OD_3002_82_readFileList_                            82
        #define OD_3002_83_readFileList_                            83
        #define OD_3002_84_readFileList_                            84
        #define OD_3002_85_readFileList_                            85
        #define OD_3002_86_readFileList_                            86
        #define OD_3002_87_readFileList_                            87
        #define OD_3002_88_readFileList_                            88
        #define OD_3002_89_readFileList_                            89
        #define OD_3002_90_readFileList_                            90
        #define OD_3002_91_readFileList_                            91
        #define OD_3002_92_readFileList_                            92
        #define OD_3002_93_readFileList_                            93
        #define OD_3002_94_readFileList_                            94
        #define OD_3002_95_readFileList_                            95
        #define OD_3002_96_readFileList_                            96
        #define OD_3002_97_readFileList_                            97
        #define OD_3002_98_readFileList_                            98
        #define OD_3002_99_readFileList_                            99
        #define OD_3002_100_readFileList_                           100
        #define OD_3002_101_readFileList_                           101
        #define OD_3002_102_readFileList_                           102
        #define OD_3002_103_readFileList_                           103
        #define OD_3002_104_readFileList_                           104
        #define OD_3002_105_readFileList_                           105
        #define OD_3002_106_readFileList_                           106
        #define OD_3002_107_readFileList_                           107
        #define OD_3002_108_readFileList_                           108
        #define OD_3002_109_readFileList_                           109
        #define OD_3002_110_readFileList_                           110
        #define OD_3002_111_readFileList_                           111
        #define OD_3002_112_readFileList_                           112
        #define OD_3002_113_readFileList_                           113
        #define OD_3002_114_readFileList_                           114
        #define OD_3002_115_readFileList_                           115
        #define OD_3002_116_readFileList_                           116
        #define OD_3002_117_readFileList_                           117
        #define OD_3002_118_readFileList_                           118
        #define OD_3002_119_readFileList_                           119
        #define OD_3002_120_readFileList_                           120
        #define OD_3002_121_readFileList_                           121
        #define OD_3002_122_readFileList_                           122
        #define OD_3002_123_readFileList_                           123
        #define OD_3002_124_readFileList_                           124
        #define OD_3002_125_readFileList_                           125
        #define OD_3002_126_readFileList_                           126
        #define OD_3002_127_readFileList_                           127

/*3003 */
        #define OD_3003_readFileControl                             0x3003

        #define OD_3003_0_readFileControl_maxSubIndex               0
        #define OD_3003_1_readFileControl_fileListIndex             1
        #define OD_3003_2_readFileControl_filename                  2
        #define OD_3003_3_readFileControl_fileData                  3
        #define OD_3003_4_readFileControl_fileSize                  4
        #define OD_3003_5_readFileControl_deleteFile                5
        #define OD_3003_6_readFileControl_totalFilesAvailable       6
        #define OD_3003_7_readFileControl_overflow                  7
        #define OD_3003_8_readFileControl_refreshFileList           8

/*3004 */
        #define OD_3004_daemonList                                  0x3004

        #define OD_3004_0_daemonList_maxSubIndex                    0
        #define OD_3004_1_daemonList_                               1
        #define OD_3004_2_daemonList_                               2
        #define OD_3004_3_daemonList_                               3
        #define OD_3004_4_daemonList_                               4
        #define OD_3004_5_daemonList_                               5
        #define OD_3004_6_daemonList_                               6
        #define OD_3004_7_daemonList_                               7
        #define OD_3004_8_daemonList_                               8
        #define OD_3004_9_daemonList_                               9
        #define OD_3004_10_daemonList_                              10
        #define OD_3004_11_daemonList_                              11
        #define OD_3004_12_daemonList_                              12
        #define OD_3004_13_daemonList_                              13
        #define OD_3004_14_daemonList_                              14
        #define OD_3004_15_daemonList_                              15
        #define OD_3004_16_daemonList_                              16
        #define OD_3004_17_daemonList_                              17
        #define OD_3004_18_daemonList_                              18
        #define OD_3004_19_daemonList_                              19
        #define OD_3004_20_daemonList_                              20
        #define OD_3004_21_daemonList_                              21
        #define OD_3004_22_daemonList_                              22
        #define OD_3004_23_daemonList_                              23
        #define OD_3004_24_daemonList_                              24
        #define OD_3004_25_daemonList_                              25
        #define OD_3004_26_daemonList_                              26
        #define OD_3004_27_daemonList_                              27
        #define OD_3004_28_daemonList_                              28
        #define OD_3004_29_daemonList_                              29
        #define OD_3004_30_daemonList_                              30
        #define OD_3004_31_daemonList_                              31
        #define OD_3004_32_daemonList_                              32
        #define OD_3004_33_daemonList_                              33
        #define OD_3004_34_daemonList_                              34
        #define OD_3004_35_daemonList_                              35
        #define OD_3004_36_daemonList_                              36
        #define OD_3004_37_daemonList_                              37
        #define OD_3004_38_daemonList_                              38
        #define OD_3004_39_daemonList_                              39
        #define OD_3004_40_daemonList_                              40
        #define OD_3004_41_daemonList_                              41
        #define OD_3004_42_daemonList_                              42
        #define OD_3004_43_daemonList_                              43
        #define OD_3004_44_daemonList_                              44
        #define OD_3004_45_daemonList_                              45
        #define OD_3004_46_daemonList_                              46
        #define OD_3004_47_daemonList_                              47
        #define OD_3004_48_daemonList_                              48
        #define OD_3004_49_daemonList_                              49
        #define OD_3004_50_daemonList_                              50
        #define OD_3004_51_daemonList_                              51
        #define OD_3004_52_daemonList_                              52
        #define OD_3004_53_daemonList_                              53
        #define OD_3004_54_daemonList_                              54
        #define OD_3004_55_daemonList_                              55
        #define OD_3004_56_daemonList_                              56
        #define OD_3004_57_daemonList_                              57
        #define OD_3004_58_daemonList_                              58
        #define OD_3004_59_daemonList_                              59
        #define OD_3004_60_daemonList_                              60
        #define OD_3004_61_daemonList_                              61
        #define OD_3004_62_daemonList_                              62
        #define OD_3004_63_daemonList_                              63
        #define OD_3004_64_daemonList_                              64
        #define OD_3004_65_daemonList_                              65
        #define OD_3004_66_daemonList_                              66
        #define OD_3004_67_daemonList_                              67
        #define OD_3004_68_daemonList_                              68
        #define OD_3004_69_daemonList_                              69
        #define OD_3004_70_daemonList_                              70
        #define OD_3004_71_daemonList_                              71
        #define OD_3004_72_daemonList_                              72
        #define OD_3004_73_daemonList_                              73
        #define OD_3004_74_daemonList_                              74
        #define OD_3004_75_daemonList_                              75
        #define OD_3004_76_daemonList_                              76
        #define OD_3004_77_daemonList_                              77
        #define OD_3004_78_daemonList_                              78
        #define OD_3004_79_daemonList_                              79
        #define OD_3004_80_daemonList_                              80
        #define OD_3004_81_daemonList_                              81
        #define OD_3004_82_daemonList_                              82
        #define OD_3004_83_daemonList_                              83
        #define OD_3004_84_daemonList_                              84
        #define OD_3004_85_daemonList_                              85
        #define OD_3004_86_daemonList_                              86
        #define OD_3004_87_daemonList_                              87
        #define OD_3004_88_daemonList_                              88
        #define OD_3004_89_daemonList_                              89
        #define OD_3004_90_daemonList_                              90
        #define OD_3004_91_daemonList_                              91
        #define OD_3004_92_daemonList_                              92
        #define OD_3004_93_daemonList_                              93
        #define OD_3004_94_daemonList_                              94
        #define OD_3004_95_daemonList_                              95
        #define OD_3004_96_daemonList_                              96
        #define OD_3004_97_daemonList_                              97
        #define OD_3004_98_daemonList_                              98
        #define OD_3004_99_daemonList_                              99
        #define OD_3004_100_daemonList_                             100
        #define OD_3004_101_daemonList_                             101
        #define OD_3004_102_daemonList_                             102
        #define OD_3004_103_daemonList_                             103
        #define OD_3004_104_daemonList_                             104
        #define OD_3004_105_daemonList_                             105
        #define OD_3004_106_daemonList_                             106
        #define OD_3004_107_daemonList_                             107
        #define OD_3004_108_daemonList_                             108
        #define OD_3004_109_daemonList_                             109
        #define OD_3004_110_daemonList_                             110
        #define OD_3004_111_daemonList_                             111
        #define OD_3004_112_daemonList_                             112
        #define OD_3004_113_daemonList_                             113
        #define OD_3004_114_daemonList_                             114
        #define OD_3004_115_daemonList_                             115
        #define OD_3004_116_daemonList_                             116
        #define OD_3004_117_daemonList_                             117
        #define OD_3004_118_daemonList_                             118
        #define OD_3004_119_daemonList_                             119
        #define OD_3004_120_daemonList_                             120
        #define OD_3004_121_daemonList_                             121
        #define OD_3004_122_daemonList_                             122
        #define OD_3004_123_daemonList_                             123
        #define OD_3004_124_daemonList_                             124
        #define OD_3004_125_daemonList_                             125
        #define OD_3004_126_daemonList_                             126
        #define OD_3004_127_daemonList_                             127

/*3005 */
        #define OD_3005_daemonManager                               0x3005

        #define OD_3005_0_daemonManager_maxSubIndex                 0
        #define OD_3005_1_daemonManager_selectApp                   1
        #define OD_3005_2_daemonManager_appName                     2
        #define OD_3005_3_daemonManager_daemonServiceName           3
        #define OD_3005_4_daemonManager_daemonCurrentState          4

/*3006 */
        #define OD_3006_syslogReader                                0x3006

        #define OD_3006_0_syslogReader_maxSubIndex                  0

/*30F0 */
        #define OD_30F0_linuxUpdaterApp                             0x30F0

        #define OD_30F0_0_linuxUpdaterApp_maxSubIndex               0
        #define OD_30F0_1_linuxUpdaterApp_currentState              1
        #define OD_30F0_2_linuxUpdaterApp_updatesAvailable          2
        #define OD_30F0_3_linuxUpdaterApp_currentUpdateFile         3
        #define OD_30F0_4_linuxUpdaterApp_errorMessage              4
        #define OD_30F0_5_linuxUpdaterApp_addUpdateFile             5
        #define OD_30F0_6_linuxUpdaterApp_startUpdate               6
        #define OD_30F0_7_linuxUpdaterApp_emergencyStopUpdate       7
        #define OD_30F0_8_linuxUpdaterApp_resetUpdater              8
        #define OD_30F0_9_linuxUpdaterApp_getAptListOutput          9

/*******************************************************************************
   STRUCTURES FOR VARIABLES IN DIFFERENT MEMORY LOCATIONS
*******************************************************************************/
#define  CO_OD_FIRST_LAST_WORD     0x55 //Any value from 0x01 to 0xFE. If changed, EEPROM will be reinitialized.

/***** Structure for RAM variables ********************************************/
struct sCO_OD_RAM{
               UNSIGNED32     FirstWord;

/*1000      */ UNSIGNED32     deviceType;
/*1001      */ UNSIGNED8      errorRegister;
/*1002      */ UNSIGNED32     manufacturerStatusRegister;
/*1003      */ UNSIGNED32      preDefinedErrorField[8];
/*1005      */ UNSIGNED32     COB_ID_SYNCMessage;
/*1006      */ UNSIGNED32     communicationCyclePeriod;
/*1007      */ UNSIGNED32     synchronousWindowLength;
/*1008      */ VISIBLE_STRING manufacturerDeviceName[11];
/*1009      */ VISIBLE_STRING manufacturerHardwareVersion[4];
/*100A      */ VISIBLE_STRING manufacturerSoftwareVersion[4];
/*1010      */ UNSIGNED32      storeParameters[1];
/*1011      */ UNSIGNED32      restoreDefaultParameters[1];
/*1014      */ UNSIGNED32     COB_ID_EMCY;
/*1015      */ UNSIGNED16     inhibitTimeEMCY;
/*1016      */ UNSIGNED32      consumerHeartbeatTime[4];
/*1017      */ UNSIGNED16     producerHeartbeatTime;
/*1018      */ OD_identity_t   identity;
/*1019      */ UNSIGNED8      synchronousCounterOverflowValue;
/*1029      */ UNSIGNED8       errorBehavior[6];
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1280      */ OD_SDOClientParameter_t SDOClientParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[4];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[4];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[4];
/*1A00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[4];
/*1F80      */ UNSIGNED32     NMTStartup;
/*2100      */ OCTET_STRING   errorStatusBits[10];
/*2101      */ UNSIGNED8      CANNodeID;
/*2102      */ UNSIGNED16     CANBitRate;
/*2103      */ UNSIGNED16     SYNCCounter;
/*2104      */ UNSIGNED16     SYNCTime;
/*2106      */ UNSIGNED32     powerOnCounter;
/*2107      */ UNSIGNED16      performance[5];
/*2108      */ INTEGER16       temperature[1];
/*2109      */ INTEGER16       voltage[1];
/*2130      */ OD_time_t       time;
/*3000      */ OD_boardInfo_t  boardInfo;
/*3001      */ OD_writeFile_t  writeFile;
/*3002      */ DOMAIN          readFileList[127];
/*3003      */ OD_readFileControl_t readFileControl;
/*3004      */ DOMAIN          daemonList[127];
/*3005      */ OD_daemonManager_t daemonManager;
/*3006      */ OD_syslogReader_t syslogReader;
/*30F0      */ OD_linuxUpdaterApp_t linuxUpdaterApp;

               UNSIGNED32     LastWord;
};

/***** Structure for ROM variables ********************************************/
struct sCO_OD_ROM{
               UNSIGNED32     FirstWord;


               UNSIGNED32     LastWord;
};

/***** Structure for EEPROM variables ********************************************/
struct sCO_OD_EEPROM{
               UNSIGNED32     FirstWord;


               UNSIGNED32     LastWord;
};

/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_ROM CO_OD_ROM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

/*******************************************************************************
   ALIASES FOR OBJECT DICTIONARY VARIABLES
*******************************************************************************/
/*1000, Data Type: UNSIGNED32 */
        #define OD_deviceType                                       CO_OD_RAM.deviceType

/*1001, Data Type: UNSIGNED8 */
        #define OD_errorRegister                                    CO_OD_RAM.errorRegister

/*1002, Data Type: UNSIGNED32 */
        #define OD_manufacturerStatusRegister                       CO_OD_RAM.manufacturerStatusRegister

/*1003, Data Type: UNSIGNED32, Array[8] */
        #define OD_preDefinedErrorField                             CO_OD_RAM.preDefinedErrorField
        #define ODL_preDefinedErrorField_arrayLength                8
        #define ODA_preDefinedErrorField_standardErrorField         0

/*1005, Data Type: UNSIGNED32 */
        #define OD_COB_ID_SYNCMessage                               CO_OD_RAM.COB_ID_SYNCMessage

/*1006, Data Type: UNSIGNED32 */
        #define OD_communicationCyclePeriod                         CO_OD_RAM.communicationCyclePeriod

/*1007, Data Type: UNSIGNED32 */
        #define OD_synchronousWindowLength                          CO_OD_RAM.synchronousWindowLength

/*1008, Data Type: VISIBLE_STRING */
        #define OD_manufacturerDeviceName                           CO_OD_RAM.manufacturerDeviceName
        #define ODL_manufacturerDeviceName_stringLength             11

/*1009, Data Type: VISIBLE_STRING */
        #define OD_manufacturerHardwareVersion                      CO_OD_RAM.manufacturerHardwareVersion
        #define ODL_manufacturerHardwareVersion_stringLength        4

/*100A, Data Type: VISIBLE_STRING */
        #define OD_manufacturerSoftwareVersion                      CO_OD_RAM.manufacturerSoftwareVersion
        #define ODL_manufacturerSoftwareVersion_stringLength        4

/*1010, Data Type: UNSIGNED32, Array[1] */
        #define OD_storeParameters                                  CO_OD_RAM.storeParameters
        #define ODL_storeParameters_arrayLength                     1
        #define ODA_storeParameters_saveAllParameters               0

/*1011, Data Type: UNSIGNED32, Array[1] */
        #define OD_restoreDefaultParameters                         CO_OD_RAM.restoreDefaultParameters
        #define ODL_restoreDefaultParameters_arrayLength            1
        #define ODA_restoreDefaultParameters_restoreAllDefaultParameters 0

/*1014, Data Type: UNSIGNED32 */
        #define OD_COB_ID_EMCY                                      CO_OD_RAM.COB_ID_EMCY

/*1015, Data Type: UNSIGNED16 */
        #define OD_inhibitTimeEMCY                                  CO_OD_RAM.inhibitTimeEMCY

/*1016, Data Type: UNSIGNED32, Array[4] */
        #define OD_consumerHeartbeatTime                            CO_OD_RAM.consumerHeartbeatTime
        #define ODL_consumerHeartbeatTime_arrayLength               4
        #define ODA_consumerHeartbeatTime_consumerHeartbeatTime     0

/*1017, Data Type: UNSIGNED16 */
        #define OD_producerHeartbeatTime                            CO_OD_RAM.producerHeartbeatTime

/*1018, Data Type: identity_t */
        #define OD_identity                                         CO_OD_RAM.identity

/*1019, Data Type: UNSIGNED8 */
        #define OD_synchronousCounterOverflowValue                  CO_OD_RAM.synchronousCounterOverflowValue

/*1029, Data Type: UNSIGNED8, Array[6] */
        #define OD_errorBehavior                                    CO_OD_RAM.errorBehavior
        #define ODL_errorBehavior_arrayLength                       6
        #define ODA_errorBehavior_communication                     0
        #define ODA_errorBehavior_communicationOther                1
        #define ODA_errorBehavior_communicationPassive              2
        #define ODA_errorBehavior_generic                           3
        #define ODA_errorBehavior_deviceProfile                     4
        #define ODA_errorBehavior_manufacturerSpecific              5

/*1200, Data Type: SDOServerParameter_t */
        #define OD_SDOServerParameter                               CO_OD_RAM.SDOServerParameter

/*1280, Data Type: SDOClientParameter_t */
        #define OD_SDOClientParameter                               CO_OD_RAM.SDOClientParameter

/*1400, Data Type: RPDOCommunicationParameter_t */
        #define OD_RPDOCommunicationParameter                       CO_OD_RAM.RPDOCommunicationParameter

/*1600, Data Type: RPDOMappingParameter_t */
        #define OD_RPDOMappingParameter                             CO_OD_RAM.RPDOMappingParameter

/*1800, Data Type: TPDOCommunicationParameter_t */
        #define OD_TPDOCommunicationParameter                       CO_OD_RAM.TPDOCommunicationParameter

/*1A00, Data Type: TPDOMappingParameter_t */
        #define OD_TPDOMappingParameter                             CO_OD_RAM.TPDOMappingParameter

/*1F80, Data Type: UNSIGNED32 */
        #define OD_NMTStartup                                       CO_OD_RAM.NMTStartup

/*2100, Data Type: OCTET_STRING */
        #define OD_errorStatusBits                                  CO_OD_RAM.errorStatusBits
        #define ODL_errorStatusBits_stringLength                    10

/*2101, Data Type: UNSIGNED8 */
        #define OD_CANNodeID                                        CO_OD_RAM.CANNodeID

/*2102, Data Type: UNSIGNED16 */
        #define OD_CANBitRate                                       CO_OD_RAM.CANBitRate

/*2103, Data Type: UNSIGNED16 */
        #define OD_SYNCCounter                                      CO_OD_RAM.SYNCCounter

/*2104, Data Type: UNSIGNED16 */
        #define OD_SYNCTime                                         CO_OD_RAM.SYNCTime

/*2106, Data Type: UNSIGNED32 */
        #define OD_powerOnCounter                                   CO_OD_RAM.powerOnCounter

/*2107, Data Type: UNSIGNED16, Array[5] */
        #define OD_performance                                      CO_OD_RAM.performance
        #define ODL_performance_arrayLength                         5
        #define ODA_performance_cyclesPerSecond                     0
        #define ODA_performance_timerCycleTime                      1
        #define ODA_performance_timerCycleMaxTime                   2
        #define ODA_performance_mainCycleTime                       3
        #define ODA_performance_mainCycleMaxTime                    4

/*2108, Data Type: INTEGER16, Array[1] */
        #define OD_temperature                                      CO_OD_RAM.temperature
        #define ODL_temperature_arrayLength                         1
        #define ODA_temperature_mainPCB                             0

/*2109, Data Type: INTEGER16, Array[1] */
        #define OD_voltage                                          CO_OD_RAM.voltage
        #define ODL_voltage_arrayLength                             1
        #define ODA_voltage_mainPCBSupply                           0

/*2130, Data Type: time_t */
        #define OD_time                                             CO_OD_RAM.time

/*3000, Data Type: boardInfo_t */
        #define OD_boardInfo                                        CO_OD_RAM.boardInfo

/*3001, Data Type: writeFile_t */
        #define OD_writeFile                                        CO_OD_RAM.writeFile

/*3002, Data Type: DOMAIN, Array[127] */
        #define OD_readFileList                                     CO_OD_RAM.readFileList
        #define ODL_readFileList_arrayLength                        127
        #define ODA_readFileList_                                   0

/*3003, Data Type: readFileControl_t */
        #define OD_readFileControl                                  CO_OD_RAM.readFileControl

/*3004, Data Type: DOMAIN, Array[127] */
        #define OD_daemonList                                       CO_OD_RAM.daemonList
        #define ODL_daemonList_arrayLength                          127
        #define ODA_daemonList_                                     0

/*3005, Data Type: daemonManager_t */
        #define OD_daemonManager                                    CO_OD_RAM.daemonManager

/*3006, Data Type: syslogReader_t */
        #define OD_syslogReader                                     CO_OD_RAM.syslogReader

/*30F0, Data Type: linuxUpdaterApp_t */
        #define OD_linuxUpdaterApp                                  CO_OD_RAM.linuxUpdaterApp

#endif
// clang-format on

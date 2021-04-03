/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode V4

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-123-g6c02323

    https://github.com/CANopenNode/CANopenNode
    https://github.com/robincornelius/libedssharp

    DON'T EDIT THIS FILE MANUALLY !!!!
********************************************************************************

    File info:
        File Names:   OD.h; OD.c
        Project File: generic.xdd
        File Version: 1

        Created:      3/9/2021 11:41:40 PM
        Created By:   Ryan Medick
        Modified:     4/3/2021 3:41:21 PM
        Modified By:  Ryan Medick

    Device Info:
        Vendor Name:  Portland State Aerospace Society
        Vendor ID:    0
        Product Name: OreSat Generic
        Product ID:   0

        Description:  OreSat Generic
*******************************************************************************/

#ifndef OD_H
#define OD_H
/*******************************************************************************
    Counters of OD objects
*******************************************************************************/
#define OD_CNT_NMT 1
#define OD_CNT_EM 1
#define OD_CNT_SYNC 1
#define OD_CNT_SYNC_PROD 1
#define OD_CNT_STORAGE 1
#define OD_CNT_EM_PROD 1
#define OD_CNT_HB_CONS 1
#define OD_CNT_HB_PROD 1
#define OD_CNT_SDO_SRV 1
#define OD_CNT_RPDO 4
#define OD_CNT_TPDO 4


/*******************************************************************************
    OD data declaration of all groups
*******************************************************************************/
typedef struct {
    uint32_t x1000_deviceType;
    char x1008_manufacturerDeviceName[21];
    char x1009_manufacturerHardwareVersion[4];
    char x100A_manufacturerSoftwareVersion[6];
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t vendor_ID;
        uint32_t productCode;
        uint32_t revisionNumber;
        uint32_t serialNumber;
    } x1018_identity;
} OD_ROM_t;

typedef struct {
    uint8_t x1001_errorRegister;
    uint32_t x1002_manufacturerStatusRegister;
    uint8_t x1003_pre_definedErrorField_sub0;
    uint32_t x1003_pre_definedErrorField[8];
    uint8_t x1010_storeParameters_sub0;
    uint32_t x1010_storeParameters[4];
    uint8_t x1011_restoreDefaultParameters_sub0;
    uint32_t x1011_restoreDefaultParameters[4];
    struct {
        uint8_t highestSub_indexSupported;
    } x1023_OSCommand;
    uint64_t x2010_SCET;
    uint64_t x2011_UTC;
    uint8_t x2100_errorStatusBits[10];
    struct {
        uint8_t highestSub_indexSupported;
        bool_t quit;
        bool_t CPUFrequency;
    } x3000_OLMControl;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t uptime;
        uint8_t numberOfCPUs;
        uint8_t CPUGovernor;
        uint16_t CPUFrequency;
        uint8_t numberOfRemoteprocs;
        uint8_t remoteprocXSelector;
        uint32_t loadAverage_1min;
        uint32_t loadAverage_5min;
        uint32_t loadAverage_15min;
        uint32_t ramTotal;
        uint32_t ramFree;
        uint32_t ramShared;
        uint32_t ramBuffered;
        uint8_t ramPercent;
        uint32_t swapTotal;
        uint32_t swapFree;
        uint8_t swapPercent;
        uint32_t procs;
        uint32_t rootParitionTotal;
        uint32_t rootParitionFree;
        uint8_t rootParitionPercent;
    } x3001_systemInfo;
    struct {
        uint8_t highestSub_indexSupported;
        uint8_t freadCacheLen;
        uint8_t fwriteCacheLen;
        uint8_t cacheSelector;
        uint32_t cacheLen;
        uint32_t iterator;
        uint32_t fileSize;
    } x3002_fileCaches;
    struct {
        uint8_t highestSub_indexSupported;
    } x3003_fread;
    struct {
        uint8_t highestSub_indexSupported;
    } x3004_fwrite;
    struct {
        uint8_t highestSub_indexSupported;
        uint8_t totalApps;
        uint8_t selectApp;
        uint8_t daemonState;
    } x3005_appManager;
    uint8_t x3006_getLog;
    struct {
        uint8_t highestSub_indexSupported;
        uint8_t status;
        uint8_t updatesAvailable;
        bool_t update;
        bool_t makeStatusFile;
    } x3100_updater;
} OD_RAM_t;

typedef struct {
    uint32_t x1005_COB_ID_SYNCMessage;
    uint32_t x1006_communicationCyclePeriod;
    uint32_t x1007_synchronousWindowLength;
    uint32_t x1014_COB_ID_EMCY;
    uint16_t x1015_inhibitTimeEMCY;
    uint8_t x1016_consumerHeartbeatTime_sub0;
    uint32_t x1016_consumerHeartbeatTime[8];
    uint16_t x1017_producerHeartbeatTime;
    uint8_t x1019_synchronousCounterOverflowValue;
    uint8_t x1029_errorBehavior_sub0;
    uint8_t x1029_errorBehavior[2];
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDClientToServer;
        uint32_t COB_IDServerToClient;
        uint8_t node_IDOfTheSDOClient;
    } x1200_SDOServerParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1400_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1401_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1402_RPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1403_RPDOCommunicationParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t mappingObject_1;
        uint32_t mappingObject_2;
        uint32_t mappingObject_3;
        uint32_t mappingObject_4;
        uint32_t mappingObject_5;
        uint32_t mappingObject_6;
        uint32_t mappingObject_7;
        uint32_t mappingObject_8;
    } x1600_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t mappingObject_1;
        uint32_t mappingObject_2;
        uint32_t mappingObject_3;
        uint32_t mappingObject_4;
        uint32_t mappingObject_5;
        uint32_t mappingObject_6;
        uint32_t mappingObject_7;
        uint32_t mappingObject_8;
    } x1601_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t mappingObject_1;
        uint32_t mappingObject_2;
        uint32_t mappingObject_3;
        uint32_t mappingObject_4;
        uint32_t mappingObject_5;
        uint32_t mappingObject_6;
        uint32_t mappingObject_7;
        uint32_t mappingObject_8;
    } x1602_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t mappingObject_1;
        uint32_t mappingObject_2;
        uint32_t mappingObject_3;
        uint32_t mappingObject_4;
        uint32_t mappingObject_5;
        uint32_t mappingObject_6;
        uint32_t mappingObject_7;
        uint32_t mappingObject_8;
    } x1603_RPDOMappingParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1800_TPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1801_TPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1802_TPDOCommunicationParameter;
    struct {
        uint8_t highestSub_indexSupported;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1803_TPDOCommunicationParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t mappingObject_1;
        uint32_t mappingObject_2;
        uint32_t mappingObject_3;
        uint32_t mappingObject_4;
        uint32_t mappingObject_5;
        uint32_t mappingObject_6;
        uint32_t mappingObject_7;
        uint32_t mappingObject_8;
    } x1A00_TPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t mappingObject_1;
        uint32_t mappingObject_2;
        uint32_t mappingObject_3;
        uint32_t mappingObject_4;
        uint32_t mappingObject_5;
        uint32_t mappingObject_6;
        uint32_t mappingObject_7;
        uint32_t mappingObject_8;
    } x1A01_TPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t mappingObject_1;
        uint32_t mappingObject_2;
        uint32_t mappingObject_3;
        uint32_t mappingObject_4;
        uint32_t mappingObject_5;
        uint32_t mappingObject_6;
        uint32_t mappingObject_7;
        uint32_t mappingObject_8;
    } x1A02_TPDOMappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t mappingObject_1;
        uint32_t mappingObject_2;
        uint32_t mappingObject_3;
        uint32_t mappingObject_4;
        uint32_t mappingObject_5;
        uint32_t mappingObject_6;
        uint32_t mappingObject_7;
        uint32_t mappingObject_8;
    } x1A03_TPDOMappingParameter;
    uint32_t x1F80_NMTStartup;
} OD_PERSIST_COMM_t;

typedef struct {
    struct {
        uint8_t highestSub_indexSupported;
        uint8_t bdefault;
        uint8_t ttoggle;
        uint8_t ntoggle;
        uint8_t ctoggle;
    } x2000_BUSManagement;
} OD_PERSIST_MFR_t;

extern OD_ROM_t OD_ROM;
extern OD_RAM_t OD_RAM;
extern OD_PERSIST_COMM_t OD_PERSIST_COMM;
extern OD_PERSIST_MFR_t OD_PERSIST_MFR;
extern OD_t *OD;


/*******************************************************************************
    Object dictionary entries - shortcuts
*******************************************************************************/
#define OD_ENTRY_H1000 &OD->list[0]
#define OD_ENTRY_H1001 &OD->list[1]
#define OD_ENTRY_H1002 &OD->list[2]
#define OD_ENTRY_H1003 &OD->list[3]
#define OD_ENTRY_H1005 &OD->list[4]
#define OD_ENTRY_H1006 &OD->list[5]
#define OD_ENTRY_H1007 &OD->list[6]
#define OD_ENTRY_H1008 &OD->list[7]
#define OD_ENTRY_H1009 &OD->list[8]
#define OD_ENTRY_H100A &OD->list[9]
#define OD_ENTRY_H1010 &OD->list[10]
#define OD_ENTRY_H1011 &OD->list[11]
#define OD_ENTRY_H1014 &OD->list[12]
#define OD_ENTRY_H1015 &OD->list[13]
#define OD_ENTRY_H1016 &OD->list[14]
#define OD_ENTRY_H1017 &OD->list[15]
#define OD_ENTRY_H1018 &OD->list[16]
#define OD_ENTRY_H1019 &OD->list[17]
#define OD_ENTRY_H1023 &OD->list[18]
#define OD_ENTRY_H1029 &OD->list[19]
#define OD_ENTRY_H1200 &OD->list[20]
#define OD_ENTRY_H1400 &OD->list[21]
#define OD_ENTRY_H1401 &OD->list[22]
#define OD_ENTRY_H1402 &OD->list[23]
#define OD_ENTRY_H1403 &OD->list[24]
#define OD_ENTRY_H1600 &OD->list[25]
#define OD_ENTRY_H1601 &OD->list[26]
#define OD_ENTRY_H1602 &OD->list[27]
#define OD_ENTRY_H1603 &OD->list[28]
#define OD_ENTRY_H1800 &OD->list[29]
#define OD_ENTRY_H1801 &OD->list[30]
#define OD_ENTRY_H1802 &OD->list[31]
#define OD_ENTRY_H1803 &OD->list[32]
#define OD_ENTRY_H1A00 &OD->list[33]
#define OD_ENTRY_H1A01 &OD->list[34]
#define OD_ENTRY_H1A02 &OD->list[35]
#define OD_ENTRY_H1A03 &OD->list[36]
#define OD_ENTRY_H1F80 &OD->list[37]
#define OD_ENTRY_H2000 &OD->list[38]
#define OD_ENTRY_H2010 &OD->list[39]
#define OD_ENTRY_H2011 &OD->list[40]
#define OD_ENTRY_H2100 &OD->list[41]
#define OD_ENTRY_H3000 &OD->list[42]
#define OD_ENTRY_H3001 &OD->list[43]
#define OD_ENTRY_H3002 &OD->list[44]
#define OD_ENTRY_H3003 &OD->list[45]
#define OD_ENTRY_H3004 &OD->list[46]
#define OD_ENTRY_H3005 &OD->list[47]
#define OD_ENTRY_H3006 &OD->list[48]
#define OD_ENTRY_H3100 &OD->list[49]


/*******************************************************************************
    Object dictionary entries - shortcuts with names
*******************************************************************************/
#define OD_ENTRY_H1000_deviceType &OD->list[0]
#define OD_ENTRY_H1001_errorRegister &OD->list[1]
#define OD_ENTRY_H1002_manufacturerStatusRegister &OD->list[2]
#define OD_ENTRY_H1003_pre_definedErrorField &OD->list[3]
#define OD_ENTRY_H1005_COB_ID_SYNCMessage &OD->list[4]
#define OD_ENTRY_H1006_communicationCyclePeriod &OD->list[5]
#define OD_ENTRY_H1007_synchronousWindowLength &OD->list[6]
#define OD_ENTRY_H1008_manufacturerDeviceName &OD->list[7]
#define OD_ENTRY_H1009_manufacturerHardwareVersion &OD->list[8]
#define OD_ENTRY_H100A_manufacturerSoftwareVersion &OD->list[9]
#define OD_ENTRY_H1010_storeParameters &OD->list[10]
#define OD_ENTRY_H1011_restoreDefaultParameters &OD->list[11]
#define OD_ENTRY_H1014_COB_ID_EMCY &OD->list[12]
#define OD_ENTRY_H1015_inhibitTimeEMCY &OD->list[13]
#define OD_ENTRY_H1016_consumerHeartbeatTime &OD->list[14]
#define OD_ENTRY_H1017_producerHeartbeatTime &OD->list[15]
#define OD_ENTRY_H1018_identity &OD->list[16]
#define OD_ENTRY_H1019_synchronousCounterOverflowValue &OD->list[17]
#define OD_ENTRY_H1023_OSCommand &OD->list[18]
#define OD_ENTRY_H1029_errorBehavior &OD->list[19]
#define OD_ENTRY_H1200_SDOServerParameter &OD->list[20]
#define OD_ENTRY_H1400_RPDOCommunicationParameter &OD->list[21]
#define OD_ENTRY_H1401_RPDOCommunicationParameter &OD->list[22]
#define OD_ENTRY_H1402_RPDOCommunicationParameter &OD->list[23]
#define OD_ENTRY_H1403_RPDOCommunicationParameter &OD->list[24]
#define OD_ENTRY_H1600_RPDOMappingParameter &OD->list[25]
#define OD_ENTRY_H1601_RPDOMappingParameter &OD->list[26]
#define OD_ENTRY_H1602_RPDOMappingParameter &OD->list[27]
#define OD_ENTRY_H1603_RPDOMappingParameter &OD->list[28]
#define OD_ENTRY_H1800_TPDOCommunicationParameter &OD->list[29]
#define OD_ENTRY_H1801_TPDOCommunicationParameter &OD->list[30]
#define OD_ENTRY_H1802_TPDOCommunicationParameter &OD->list[31]
#define OD_ENTRY_H1803_TPDOCommunicationParameter &OD->list[32]
#define OD_ENTRY_H1A00_TPDOMappingParameter &OD->list[33]
#define OD_ENTRY_H1A01_TPDOMappingParameter &OD->list[34]
#define OD_ENTRY_H1A02_TPDOMappingParameter &OD->list[35]
#define OD_ENTRY_H1A03_TPDOMappingParameter &OD->list[36]
#define OD_ENTRY_H1F80_NMTStartup &OD->list[37]
#define OD_ENTRY_H2000_BUSManagement &OD->list[38]
#define OD_ENTRY_H2010_SCET &OD->list[39]
#define OD_ENTRY_H2011_UTC &OD->list[40]
#define OD_ENTRY_H2100_errorStatusBits &OD->list[41]
#define OD_ENTRY_H3000_OLMControl &OD->list[42]
#define OD_ENTRY_H3001_systemInfo &OD->list[43]
#define OD_ENTRY_H3002_fileCaches &OD->list[44]
#define OD_ENTRY_H3003_fread &OD->list[45]
#define OD_ENTRY_H3004_fwrite &OD->list[46]
#define OD_ENTRY_H3005_appManager &OD->list[47]
#define OD_ENTRY_H3006_getLog &OD->list[48]
#define OD_ENTRY_H3100_updater &OD->list[49]

#endif /* OD_H */

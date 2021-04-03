/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode V4

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-123-g6c02323

    https://github.com/CANopenNode/CANopenNode
    https://github.com/robincornelius/libedssharp

    DON'T EDIT THIS FILE MANUALLY, UNLESS YOU KNOW WHAT YOU ARE DOING !!!!
*******************************************************************************/

#define OD_DEFINITION
#include "301/CO_ODinterface.h"
#include "OD.h"

#if CO_VERSION_MAJOR < 4
#error This Object dictionary is compatible with CANopenNode V4.0 and above!
#endif

/*******************************************************************************
    OD data initialization of all groups
*******************************************************************************/
OD_ROM_t OD_ROM = {
    .x1000_deviceType = 0x00000000,
    .x1008_manufacturerDeviceName = {'O', 'r', 'e', 'S', 'a', 't', ' ', 'L', 'i', 'n', 'u', 'x', ' ', 'G', 'e', 'n', 'e', 'r', 'i', 'c', 0},
    .x1009_manufacturerHardwareVersion = {'0', '.', '0', 0},
    .x100A_manufacturerSoftwareVersion = {'0', '.', '0', '.', '0', 0},
    .x1018_identity = {
        .highestSub_indexSupported = 0x04,
        .vendor_ID = 0x00000000,
        .productCode = 0x00000000,
        .revisionNumber = 0x00000000,
        .serialNumber = 0x00000000
    }
};

OD_RAM_t OD_RAM = {
    .x1001_errorRegister = 0x00,
    .x1002_manufacturerStatusRegister = 0x00000000,
    .x1003_pre_definedErrorField_sub0 = 0x00,
    .x1003_pre_definedErrorField = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    .x1010_storeParameters_sub0 = 0x04,
    .x1010_storeParameters = {0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .x1011_restoreDefaultParameters_sub0 = 0x04,
    .x1011_restoreDefaultParameters = {0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .x1023_OSCommand = {
        .highestSub_indexSupported = 0x03
    },
    .x2010_SCET = 0x0000000000000000,
    .x2011_UTC = 0x0000000000000000,
    .x2100_errorStatusBits = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .x3000_OLMControl = {
        .highestSub_indexSupported = 0x04,
        .quit = false,
        .CPUFrequency = false
    },
    .x3001_systemInfo = {
        .highestSub_indexSupported = 0x1C,
        .uptime = 0x00000000,
        .numberOfCPUs = 0x00,
        .CPUGovernor = 0x00,
        .CPUFrequency = 0x0000,
        .numberOfRemoteprocs = 0x00,
        .remoteprocXSelector = 0x00,
        .loadAverage_1min = 0x00000000,
        .loadAverage_5min = 0x00000000,
        .loadAverage_15min = 0x00000000,
        .ramTotal = 0x00000000,
        .ramFree = 0x00000000,
        .ramShared = 0x00000000,
        .ramBuffered = 0x00000000,
        .ramPercent = 0x00,
        .swapTotal = 0x00000000,
        .swapFree = 0x00000000,
        .swapPercent = 0x00,
        .procs = 0x00000000,
        .rootParitionTotal = 0x00000000,
        .rootParitionFree = 0x00000000,
        .rootParitionPercent = 0x00
    },
    .x3002_fileCaches = {
        .highestSub_indexSupported = 0x09,
        .freadCacheLen = 0x00,
        .fwriteCacheLen = 0x00,
        .cacheSelector = 0x00,
        .cacheLen = 0x00000000,
        .iterator = 0x00000000,
        .fileSize = 0x00000000
    },
    .x3003_fread = {
        .highestSub_indexSupported = 0x04
    },
    .x3004_fwrite = {
        .highestSub_indexSupported = 0x03
    },
    .x3005_appManager = {
        .highestSub_indexSupported = 0x04,
        .totalApps = 0x00,
        .selectApp = 0x00,
        .daemonState = 0x00
    },
    .x3006_getLog = 0x00,
    .x3100_updater = {
        .highestSub_indexSupported = 0x05,
        .status = 0x00,
        .updatesAvailable = 0x00,
        .update = false,
        .makeStatusFile = false
    }
};

OD_PERSIST_COMM_t OD_PERSIST_COMM = {
    .x1005_COB_ID_SYNCMessage = 0x00000080,
    .x1006_communicationCyclePeriod = 0x00000000,
    .x1007_synchronousWindowLength = 0x00000000,
    .x1014_COB_ID_EMCY = 0x00000080,
    .x1015_inhibitTimeEMCY = 0x0000,
    .x1016_consumerHeartbeatTime_sub0 = 0x08,
    .x1016_consumerHeartbeatTime = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    .x1017_producerHeartbeatTime = 0x03E8,
    .x1019_synchronousCounterOverflowValue = 0x00,
    .x1029_errorBehavior_sub0 = 0x02,
    .x1029_errorBehavior = {0x00, 0x00},
    .x1200_SDOServerParameter = {
        .highestSub_indexSupported = 0x03,
        .COB_IDClientToServer = 0x80000000,
        .COB_IDServerToClient = 0x80000000,
        .node_IDOfTheSDOClient = 0x01
    },
    .x1400_RPDOCommunicationParameter = {
        .highestSub_indexSupported = 0x05,
        .COB_IDUsedByRPDO = 0x80000200,
        .transmissionType = 0xFE,
        .eventTimer = 0x0000
    },
    .x1401_RPDOCommunicationParameter = {
        .highestSub_indexSupported = 0x05,
        .COB_IDUsedByRPDO = 0x80000300,
        .transmissionType = 0xFE,
        .eventTimer = 0x0000
    },
    .x1402_RPDOCommunicationParameter = {
        .highestSub_indexSupported = 0x05,
        .COB_IDUsedByRPDO = 0x80000400,
        .transmissionType = 0xFE,
        .eventTimer = 0x0000
    },
    .x1403_RPDOCommunicationParameter = {
        .highestSub_indexSupported = 0x05,
        .COB_IDUsedByRPDO = 0x80000500,
        .transmissionType = 0xFE,
        .eventTimer = 0x0000
    },
    .x1600_RPDOMappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x00,
        .mappingObject_1 = 0x00000000,
        .mappingObject_2 = 0x00000000,
        .mappingObject_3 = 0x00000000,
        .mappingObject_4 = 0x00000000,
        .mappingObject_5 = 0x00000000,
        .mappingObject_6 = 0x00000000,
        .mappingObject_7 = 0x00000000,
        .mappingObject_8 = 0x00000000
    },
    .x1601_RPDOMappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x00,
        .mappingObject_1 = 0x00000000,
        .mappingObject_2 = 0x00000000,
        .mappingObject_3 = 0x00000000,
        .mappingObject_4 = 0x00000000,
        .mappingObject_5 = 0x00000000,
        .mappingObject_6 = 0x00000000,
        .mappingObject_7 = 0x00000000,
        .mappingObject_8 = 0x00000000
    },
    .x1602_RPDOMappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x00,
        .mappingObject_1 = 0x00000000,
        .mappingObject_2 = 0x00000000,
        .mappingObject_3 = 0x00000000,
        .mappingObject_4 = 0x00000000,
        .mappingObject_5 = 0x00000000,
        .mappingObject_6 = 0x00000000,
        .mappingObject_7 = 0x00000000,
        .mappingObject_8 = 0x00000000
    },
    .x1603_RPDOMappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x00,
        .mappingObject_1 = 0x00000000,
        .mappingObject_2 = 0x00000000,
        .mappingObject_3 = 0x00000000,
        .mappingObject_4 = 0x00000000,
        .mappingObject_5 = 0x00000000,
        .mappingObject_6 = 0x00000000,
        .mappingObject_7 = 0x00000000,
        .mappingObject_8 = 0x00000000
    },
    .x1800_TPDOCommunicationParameter = {
        .highestSub_indexSupported = 0x06,
        .COB_IDUsedByTPDO = 0xC0000180,
        .transmissionType = 0xFE,
        .inhibitTime = 0x0000,
        .compatibilityEntry = 0x00,
        .eventTimer = 0x0000,
        .SYNCStartValue = 0x00
    },
    .x1801_TPDOCommunicationParameter = {
        .highestSub_indexSupported = 0x06,
        .COB_IDUsedByTPDO = 0xC0000280,
        .transmissionType = 0xFE,
        .inhibitTime = 0x0000,
        .compatibilityEntry = 0x00,
        .eventTimer = 0x0000,
        .SYNCStartValue = 0x00
    },
    .x1802_TPDOCommunicationParameter = {
        .highestSub_indexSupported = 0x06,
        .COB_IDUsedByTPDO = 0xC0000380,
        .transmissionType = 0xFE,
        .inhibitTime = 0x0000,
        .compatibilityEntry = 0x00,
        .eventTimer = 0x0000,
        .SYNCStartValue = 0x00
    },
    .x1803_TPDOCommunicationParameter = {
        .highestSub_indexSupported = 0x06,
        .COB_IDUsedByTPDO = 0xC0000480,
        .transmissionType = 0xFE,
        .inhibitTime = 0x0000,
        .compatibilityEntry = 0x00,
        .eventTimer = 0x0000,
        .SYNCStartValue = 0x00
    },
    .x1A00_TPDOMappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x00,
        .mappingObject_1 = 0x00000000,
        .mappingObject_2 = 0x00000000,
        .mappingObject_3 = 0x00000000,
        .mappingObject_4 = 0x00000000,
        .mappingObject_5 = 0x00000000,
        .mappingObject_6 = 0x00000000,
        .mappingObject_7 = 0x00000000,
        .mappingObject_8 = 0x00000000
    },
    .x1A01_TPDOMappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x00,
        .mappingObject_1 = 0x00000000,
        .mappingObject_2 = 0x00000000,
        .mappingObject_3 = 0x00000000,
        .mappingObject_4 = 0x00000000,
        .mappingObject_5 = 0x00000000,
        .mappingObject_6 = 0x00000000,
        .mappingObject_7 = 0x00000000,
        .mappingObject_8 = 0x00000000
    },
    .x1A02_TPDOMappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x00,
        .mappingObject_1 = 0x00000000,
        .mappingObject_2 = 0x00000000,
        .mappingObject_3 = 0x00000000,
        .mappingObject_4 = 0x00000000,
        .mappingObject_5 = 0x00000000,
        .mappingObject_6 = 0x00000000,
        .mappingObject_7 = 0x00000000,
        .mappingObject_8 = 0x00000000
    },
    .x1A03_TPDOMappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x00,
        .mappingObject_1 = 0x00000000,
        .mappingObject_2 = 0x00000000,
        .mappingObject_3 = 0x00000000,
        .mappingObject_4 = 0x00000000,
        .mappingObject_5 = 0x00000000,
        .mappingObject_6 = 0x00000000,
        .mappingObject_7 = 0x00000000,
        .mappingObject_8 = 0x00000000
    },
    .x1F80_NMTStartup = 0x00000008
};

OD_PERSIST_MFR_t OD_PERSIST_MFR = {
    .x2000_BUSManagement = {
        .highestSub_indexSupported = 0x04,
        .bdefault = 0x00,
        .ttoggle = 0x00,
        .ntoggle = 0x00,
        .ctoggle = 0x00
    }
};



/*******************************************************************************
    All OD objects (constant definitions)
*******************************************************************************/
typedef struct {
    OD_obj_var_t o_1000_deviceType;
    OD_obj_var_t o_1001_errorRegister;
    OD_obj_var_t o_1002_manufacturerStatusRegister;
    OD_obj_array_t o_1003_pre_definedErrorField;
    OD_obj_var_t o_1005_COB_ID_SYNCMessage;
    OD_obj_var_t o_1006_communicationCyclePeriod;
    OD_obj_var_t o_1007_synchronousWindowLength;
    OD_obj_var_t o_1008_manufacturerDeviceName;
    OD_obj_var_t o_1009_manufacturerHardwareVersion;
    OD_obj_var_t o_100A_manufacturerSoftwareVersion;
    OD_obj_array_t o_1010_storeParameters;
    OD_obj_array_t o_1011_restoreDefaultParameters;
    OD_obj_var_t o_1014_COB_ID_EMCY;
    OD_obj_var_t o_1015_inhibitTimeEMCY;
    OD_obj_array_t o_1016_consumerHeartbeatTime;
    OD_obj_var_t o_1017_producerHeartbeatTime;
    OD_obj_record_t o_1018_identity[5];
    OD_obj_var_t o_1019_synchronousCounterOverflowValue;
    OD_obj_record_t o_1023_OSCommand[4];
    OD_obj_array_t o_1029_errorBehavior;
    OD_obj_record_t o_1200_SDOServerParameter[4];
    OD_obj_record_t o_1400_RPDOCommunicationParameter[4];
    OD_obj_record_t o_1401_RPDOCommunicationParameter[4];
    OD_obj_record_t o_1402_RPDOCommunicationParameter[4];
    OD_obj_record_t o_1403_RPDOCommunicationParameter[4];
    OD_obj_record_t o_1600_RPDOMappingParameter[9];
    OD_obj_record_t o_1601_RPDOMappingParameter[9];
    OD_obj_record_t o_1602_RPDOMappingParameter[9];
    OD_obj_record_t o_1603_RPDOMappingParameter[9];
    OD_obj_record_t o_1800_TPDOCommunicationParameter[7];
    OD_obj_record_t o_1801_TPDOCommunicationParameter[7];
    OD_obj_record_t o_1802_TPDOCommunicationParameter[7];
    OD_obj_record_t o_1803_TPDOCommunicationParameter[7];
    OD_obj_record_t o_1A00_TPDOMappingParameter[9];
    OD_obj_record_t o_1A01_TPDOMappingParameter[9];
    OD_obj_record_t o_1A02_TPDOMappingParameter[9];
    OD_obj_record_t o_1A03_TPDOMappingParameter[9];
    OD_obj_var_t o_1F80_NMTStartup;
    OD_obj_record_t o_2000_BUSManagement[5];
    OD_obj_var_t o_2010_SCET;
    OD_obj_var_t o_2011_UTC;
    OD_obj_var_t o_2100_errorStatusBits;
    OD_obj_record_t o_3000_OLMControl[5];
    OD_obj_record_t o_3001_systemInfo[29];
    OD_obj_record_t o_3002_fileCaches[10];
    OD_obj_record_t o_3003_fread[5];
    OD_obj_record_t o_3004_fwrite[4];
    OD_obj_record_t o_3005_appManager[5];
    OD_obj_var_t o_3006_getLog;
    OD_obj_record_t o_3100_updater[6];
} ODObjs_t;

static CO_PROGMEM ODObjs_t ODObjs = {
    .o_1000_deviceType = {
        .dataOrig = &OD_ROM.x1000_deviceType,
        .attribute = ODA_SDO_R | ODA_MB,
        .dataLength = 4
    },
    .o_1001_errorRegister = {
        .dataOrig = &OD_RAM.x1001_errorRegister,
        .attribute = ODA_SDO_R | ODA_TRPDO,
        .dataLength = 1
    },
    .o_1002_manufacturerStatusRegister = {
        .dataOrig = &OD_RAM.x1002_manufacturerStatusRegister,
        .attribute = ODA_SDO_R | ODA_TRPDO | ODA_MB,
        .dataLength = 4
    },
    .o_1003_pre_definedErrorField = {
        .dataOrig0 = &OD_RAM.x1003_pre_definedErrorField_sub0,
        .dataOrig = &OD_RAM.x1003_pre_definedErrorField[0],
        .attribute0 = ODA_SDO_RW,
        .attribute = ODA_SDO_R | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_1005_COB_ID_SYNCMessage = {
        .dataOrig = &OD_PERSIST_COMM.x1005_COB_ID_SYNCMessage,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1006_communicationCyclePeriod = {
        .dataOrig = &OD_PERSIST_COMM.x1006_communicationCyclePeriod,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1007_synchronousWindowLength = {
        .dataOrig = &OD_PERSIST_COMM.x1007_synchronousWindowLength,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1008_manufacturerDeviceName = {
        .dataOrig = &OD_ROM.x1008_manufacturerDeviceName[0],
        .attribute = ODA_SDO_R | ODA_STR,
        .dataLength = 20
    },
    .o_1009_manufacturerHardwareVersion = {
        .dataOrig = &OD_ROM.x1009_manufacturerHardwareVersion[0],
        .attribute = ODA_SDO_R | ODA_STR,
        .dataLength = 3
    },
    .o_100A_manufacturerSoftwareVersion = {
        .dataOrig = &OD_ROM.x100A_manufacturerSoftwareVersion[0],
        .attribute = ODA_SDO_R | ODA_STR,
        .dataLength = 5
    },
    .o_1010_storeParameters = {
        .dataOrig0 = &OD_RAM.x1010_storeParameters_sub0,
        .dataOrig = &OD_RAM.x1010_storeParameters[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_1011_restoreDefaultParameters = {
        .dataOrig0 = &OD_RAM.x1011_restoreDefaultParameters_sub0,
        .dataOrig = &OD_RAM.x1011_restoreDefaultParameters[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_1014_COB_ID_EMCY = {
        .dataOrig = &OD_PERSIST_COMM.x1014_COB_ID_EMCY,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1015_inhibitTimeEMCY = {
        .dataOrig = &OD_PERSIST_COMM.x1015_inhibitTimeEMCY,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 2
    },
    .o_1016_consumerHeartbeatTime = {
        .dataOrig0 = &OD_PERSIST_COMM.x1016_consumerHeartbeatTime_sub0,
        .dataOrig = &OD_PERSIST_COMM.x1016_consumerHeartbeatTime[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_1017_producerHeartbeatTime = {
        .dataOrig = &OD_PERSIST_COMM.x1017_producerHeartbeatTime,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 2
    },
    .o_1018_identity = {
        {
            .dataOrig = &OD_ROM.x1018_identity.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.vendor_ID,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.productCode,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.revisionNumber,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.serialNumber,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1019_synchronousCounterOverflowValue = {
        .dataOrig = &OD_PERSIST_COMM.x1019_synchronousCounterOverflowValue,
        .attribute = ODA_SDO_RW,
        .dataLength = 1
    },
    .o_1023_OSCommand = {
        {
            .dataOrig = &OD_RAM.x1023_OSCommand.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 1,
            .attribute = ODA_SDO_RW,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 3,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        }
    },
    .o_1029_errorBehavior = {
        .dataOrig0 = &OD_PERSIST_COMM.x1029_errorBehavior_sub0,
        .dataOrig = &OD_PERSIST_COMM.x1029_errorBehavior[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW,
        .dataElementLength = 1,
        .dataElementSizeof = sizeof(uint8_t)
    },
    .o_1200_SDOServerParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1200_SDOServerParameter.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1200_SDOServerParameter.COB_IDClientToServer,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1200_SDOServerParameter.COB_IDServerToClient,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1200_SDOServerParameter.node_IDOfTheSDOClient,
            .subIndex = 3,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        }
    },
    .o_1400_RPDOCommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1400_RPDOCommunicationParameter.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1400_RPDOCommunicationParameter.COB_IDUsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1400_RPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1400_RPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        }
    },
    .o_1401_RPDOCommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1401_RPDOCommunicationParameter.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1401_RPDOCommunicationParameter.COB_IDUsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1401_RPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1401_RPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        }
    },
    .o_1402_RPDOCommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1402_RPDOCommunicationParameter.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1402_RPDOCommunicationParameter.COB_IDUsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1402_RPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1402_RPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        }
    },
    .o_1403_RPDOCommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1403_RPDOCommunicationParameter.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1403_RPDOCommunicationParameter.COB_IDUsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1403_RPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1403_RPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        }
    },
    .o_1600_RPDOMappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDOMappingParameter.mappingObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDOMappingParameter.mappingObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDOMappingParameter.mappingObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDOMappingParameter.mappingObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDOMappingParameter.mappingObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDOMappingParameter.mappingObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDOMappingParameter.mappingObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDOMappingParameter.mappingObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1601_RPDOMappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDOMappingParameter.mappingObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDOMappingParameter.mappingObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDOMappingParameter.mappingObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDOMappingParameter.mappingObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDOMappingParameter.mappingObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDOMappingParameter.mappingObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDOMappingParameter.mappingObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDOMappingParameter.mappingObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1602_RPDOMappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDOMappingParameter.mappingObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDOMappingParameter.mappingObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDOMappingParameter.mappingObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDOMappingParameter.mappingObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDOMappingParameter.mappingObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDOMappingParameter.mappingObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDOMappingParameter.mappingObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDOMappingParameter.mappingObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1603_RPDOMappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDOMappingParameter.mappingObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDOMappingParameter.mappingObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDOMappingParameter.mappingObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDOMappingParameter.mappingObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDOMappingParameter.mappingObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDOMappingParameter.mappingObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDOMappingParameter.mappingObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDOMappingParameter.mappingObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1800_TPDOCommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDOCommunicationParameter.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDOCommunicationParameter.COB_IDUsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDOCommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDOCommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDOCommunicationParameter.SYNCStartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        }
    },
    .o_1801_TPDOCommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDOCommunicationParameter.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDOCommunicationParameter.COB_IDUsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDOCommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDOCommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDOCommunicationParameter.SYNCStartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        }
    },
    .o_1802_TPDOCommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDOCommunicationParameter.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDOCommunicationParameter.COB_IDUsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDOCommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDOCommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDOCommunicationParameter.SYNCStartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        }
    },
    .o_1803_TPDOCommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDOCommunicationParameter.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDOCommunicationParameter.COB_IDUsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDOCommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDOCommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDOCommunicationParameter.SYNCStartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        }
    },
    .o_1A00_TPDOMappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDOMappingParameter.mappingObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDOMappingParameter.mappingObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDOMappingParameter.mappingObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDOMappingParameter.mappingObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDOMappingParameter.mappingObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDOMappingParameter.mappingObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDOMappingParameter.mappingObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDOMappingParameter.mappingObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1A01_TPDOMappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDOMappingParameter.mappingObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDOMappingParameter.mappingObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDOMappingParameter.mappingObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDOMappingParameter.mappingObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDOMappingParameter.mappingObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDOMappingParameter.mappingObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDOMappingParameter.mappingObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDOMappingParameter.mappingObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1A02_TPDOMappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDOMappingParameter.mappingObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDOMappingParameter.mappingObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDOMappingParameter.mappingObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDOMappingParameter.mappingObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDOMappingParameter.mappingObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDOMappingParameter.mappingObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDOMappingParameter.mappingObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDOMappingParameter.mappingObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1A03_TPDOMappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDOMappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDOMappingParameter.mappingObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDOMappingParameter.mappingObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDOMappingParameter.mappingObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDOMappingParameter.mappingObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDOMappingParameter.mappingObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDOMappingParameter.mappingObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDOMappingParameter.mappingObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDOMappingParameter.mappingObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1F80_NMTStartup = {
        .dataOrig = &OD_PERSIST_COMM.x1F80_NMTStartup,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_2000_BUSManagement = {
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUSManagement.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUSManagement.bdefault,
            .subIndex = 1,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUSManagement.ttoggle,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUSManagement.ntoggle,
            .subIndex = 3,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUSManagement.ctoggle,
            .subIndex = 4,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        }
    },
    .o_2010_SCET = {
        .dataOrig = &OD_RAM.x2010_SCET,
        .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
        .dataLength = 8
    },
    .o_2011_UTC = {
        .dataOrig = &OD_RAM.x2011_UTC,
        .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
        .dataLength = 8
    },
    .o_2100_errorStatusBits = {
        .dataOrig = &OD_RAM.x2100_errorStatusBits[0],
        .attribute = ODA_SDO_R,
        .dataLength = 10
    },
    .o_3000_OLMControl = {
        {
            .dataOrig = &OD_RAM.x3000_OLMControl.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 1,
            .attribute = ODA_SDO_W,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 2,
            .attribute = ODA_SDO_W,
            .dataLength = 0
        },
        {
            .dataOrig = &OD_RAM.x3000_OLMControl.quit,
            .subIndex = 3,
            .attribute = ODA_SDO_W,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3000_OLMControl.CPUFrequency,
            .subIndex = 4,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        }
    },
    .o_3001_systemInfo = {
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 1,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 3,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.uptime,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.numberOfCPUs,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 7,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.CPUGovernor,
            .subIndex = 8,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.CPUFrequency,
            .subIndex = 9,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.numberOfRemoteprocs,
            .subIndex = 10,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.remoteprocXSelector,
            .subIndex = 11,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 12,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 13,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.loadAverage_1min,
            .subIndex = 14,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.loadAverage_5min,
            .subIndex = 15,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.loadAverage_15min,
            .subIndex = 16,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.ramTotal,
            .subIndex = 17,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.ramFree,
            .subIndex = 18,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.ramShared,
            .subIndex = 19,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.ramBuffered,
            .subIndex = 20,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.ramPercent,
            .subIndex = 21,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.swapTotal,
            .subIndex = 22,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.swapFree,
            .subIndex = 23,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.swapPercent,
            .subIndex = 24,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.procs,
            .subIndex = 25,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.rootParitionTotal,
            .subIndex = 26,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.rootParitionFree,
            .subIndex = 27,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3001_systemInfo.rootParitionPercent,
            .subIndex = 28,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        }
    },
    .o_3002_fileCaches = {
        {
            .dataOrig = &OD_RAM.x3002_fileCaches.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3002_fileCaches.freadCacheLen,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3002_fileCaches.fwriteCacheLen,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3002_fileCaches.cacheSelector,
            .subIndex = 3,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 4,
            .attribute = ODA_SDO_RW,
            .dataLength = 0
        },
        {
            .dataOrig = &OD_RAM.x3002_fileCaches.cacheLen,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x3002_fileCaches.iterator,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = NULL,
            .subIndex = 7,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = &OD_RAM.x3002_fileCaches.fileSize,
            .subIndex = 8,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = NULL,
            .subIndex = 9,
            .attribute = ODA_SDO_W,
            .dataLength = 0
        }
    },
    .o_3003_fread = {
        {
            .dataOrig = &OD_RAM.x3003_fread.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 1,
            .attribute = ODA_SDO_RW,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 3,
            .attribute = ODA_SDO_W,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 4,
            .attribute = ODA_SDO_W,
            .dataLength = 0
        }
    },
    .o_3004_fwrite = {
        {
            .dataOrig = &OD_RAM.x3004_fwrite.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 1,
            .attribute = ODA_SDO_RW,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 2,
            .attribute = ODA_SDO_W,
            .dataLength = 0
        },
        {
            .dataOrig = NULL,
            .subIndex = 3,
            .attribute = ODA_SDO_W,
            .dataLength = 0
        }
    },
    .o_3005_appManager = {
        {
            .dataOrig = &OD_RAM.x3005_appManager.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3005_appManager.totalApps,
            .subIndex = 1,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3005_appManager.selectApp,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 3,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = &OD_RAM.x3005_appManager.daemonState,
            .subIndex = 4,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        }
    },
    .o_3006_getLog = {
        .dataOrig = &OD_RAM.x3006_getLog,
        .attribute = ODA_SDO_RW,
        .dataLength = 1
    },
    .o_3100_updater = {
        {
            .dataOrig = &OD_RAM.x3100_updater.highestSub_indexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3100_updater.status,
            .subIndex = 1,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3100_updater.updatesAvailable,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = NULL,
            .subIndex = 3,
            .attribute = ODA_SDO_R,
            .dataLength = 0
        },
        {
            .dataOrig = &OD_RAM.x3100_updater.update,
            .subIndex = 4,
            .attribute = ODA_SDO_W | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3100_updater.makeStatusFile,
            .subIndex = 5,
            .attribute = ODA_SDO_W | ODA_TPDO,
            .dataLength = 1
        }
    }
};


/*******************************************************************************
    Object dictionary
*******************************************************************************/
static OD_entry_t ODList[] = {
    {0x1000, 0x01, ODT_VAR, &ODObjs.o_1000_deviceType, NULL},
    {0x1001, 0x01, ODT_VAR, &ODObjs.o_1001_errorRegister, NULL},
    {0x1002, 0x01, ODT_VAR, &ODObjs.o_1002_manufacturerStatusRegister, NULL},
    {0x1003, 0x09, ODT_ARR, &ODObjs.o_1003_pre_definedErrorField, NULL},
    {0x1005, 0x01, ODT_VAR, &ODObjs.o_1005_COB_ID_SYNCMessage, NULL},
    {0x1006, 0x01, ODT_VAR, &ODObjs.o_1006_communicationCyclePeriod, NULL},
    {0x1007, 0x01, ODT_VAR, &ODObjs.o_1007_synchronousWindowLength, NULL},
    {0x1008, 0x01, ODT_VAR, &ODObjs.o_1008_manufacturerDeviceName, NULL},
    {0x1009, 0x01, ODT_VAR, &ODObjs.o_1009_manufacturerHardwareVersion, NULL},
    {0x100A, 0x01, ODT_VAR, &ODObjs.o_100A_manufacturerSoftwareVersion, NULL},
    {0x1010, 0x05, ODT_ARR, &ODObjs.o_1010_storeParameters, NULL},
    {0x1011, 0x05, ODT_ARR, &ODObjs.o_1011_restoreDefaultParameters, NULL},
    {0x1014, 0x01, ODT_VAR, &ODObjs.o_1014_COB_ID_EMCY, NULL},
    {0x1015, 0x01, ODT_VAR, &ODObjs.o_1015_inhibitTimeEMCY, NULL},
    {0x1016, 0x09, ODT_ARR, &ODObjs.o_1016_consumerHeartbeatTime, NULL},
    {0x1017, 0x01, ODT_VAR, &ODObjs.o_1017_producerHeartbeatTime, NULL},
    {0x1018, 0x05, ODT_REC, &ODObjs.o_1018_identity, NULL},
    {0x1019, 0x01, ODT_VAR, &ODObjs.o_1019_synchronousCounterOverflowValue, NULL},
    {0x1023, 0x04, ODT_REC, &ODObjs.o_1023_OSCommand, NULL},
    {0x1029, 0x03, ODT_ARR, &ODObjs.o_1029_errorBehavior, NULL},
    {0x1200, 0x04, ODT_REC, &ODObjs.o_1200_SDOServerParameter, NULL},
    {0x1400, 0x04, ODT_REC, &ODObjs.o_1400_RPDOCommunicationParameter, NULL},
    {0x1401, 0x04, ODT_REC, &ODObjs.o_1401_RPDOCommunicationParameter, NULL},
    {0x1402, 0x04, ODT_REC, &ODObjs.o_1402_RPDOCommunicationParameter, NULL},
    {0x1403, 0x04, ODT_REC, &ODObjs.o_1403_RPDOCommunicationParameter, NULL},
    {0x1600, 0x09, ODT_REC, &ODObjs.o_1600_RPDOMappingParameter, NULL},
    {0x1601, 0x09, ODT_REC, &ODObjs.o_1601_RPDOMappingParameter, NULL},
    {0x1602, 0x09, ODT_REC, &ODObjs.o_1602_RPDOMappingParameter, NULL},
    {0x1603, 0x09, ODT_REC, &ODObjs.o_1603_RPDOMappingParameter, NULL},
    {0x1800, 0x07, ODT_REC, &ODObjs.o_1800_TPDOCommunicationParameter, NULL},
    {0x1801, 0x07, ODT_REC, &ODObjs.o_1801_TPDOCommunicationParameter, NULL},
    {0x1802, 0x07, ODT_REC, &ODObjs.o_1802_TPDOCommunicationParameter, NULL},
    {0x1803, 0x07, ODT_REC, &ODObjs.o_1803_TPDOCommunicationParameter, NULL},
    {0x1A00, 0x09, ODT_REC, &ODObjs.o_1A00_TPDOMappingParameter, NULL},
    {0x1A01, 0x09, ODT_REC, &ODObjs.o_1A01_TPDOMappingParameter, NULL},
    {0x1A02, 0x09, ODT_REC, &ODObjs.o_1A02_TPDOMappingParameter, NULL},
    {0x1A03, 0x09, ODT_REC, &ODObjs.o_1A03_TPDOMappingParameter, NULL},
    {0x1F80, 0x01, ODT_VAR, &ODObjs.o_1F80_NMTStartup, NULL},
    {0x2000, 0x05, ODT_REC, &ODObjs.o_2000_BUSManagement, NULL},
    {0x2010, 0x01, ODT_VAR, &ODObjs.o_2010_SCET, NULL},
    {0x2011, 0x01, ODT_VAR, &ODObjs.o_2011_UTC, NULL},
    {0x2100, 0x01, ODT_VAR, &ODObjs.o_2100_errorStatusBits, NULL},
    {0x3000, 0x05, ODT_REC, &ODObjs.o_3000_OLMControl, NULL},
    {0x3001, 0x1D, ODT_REC, &ODObjs.o_3001_systemInfo, NULL},
    {0x3002, 0x0A, ODT_REC, &ODObjs.o_3002_fileCaches, NULL},
    {0x3003, 0x05, ODT_REC, &ODObjs.o_3003_fread, NULL},
    {0x3004, 0x04, ODT_REC, &ODObjs.o_3004_fwrite, NULL},
    {0x3005, 0x05, ODT_REC, &ODObjs.o_3005_appManager, NULL},
    {0x3006, 0x01, ODT_VAR, &ODObjs.o_3006_getLog, NULL},
    {0x3100, 0x06, ODT_REC, &ODObjs.o_3100_updater, NULL},
    {0x0000, 0x00, 0, NULL, NULL}
};

static OD_t _OD = {
    (sizeof(ODList) / sizeof(ODList[0])) - 1,
    &ODList[0]
};

OD_t *OD = &_OD;

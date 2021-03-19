// clang-format off
/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode v1 to v2

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-123-g6c02323

    https://github.com/CANopenNode/CANopenNode
    https://github.com/robincornelius/libedssharp

    DON'T EDIT THIS FILE MANUALLY !!!!
*******************************************************************************/
// For CANopenNode V2 users, C macro `CO_VERSION_MAJOR=2` has to be added to project options
#ifndef CO_VERSION_MAJOR
 #include "CO_driver.h"
 #include "CO_OD.h"
 #include "CO_SDO.h"
#elif CO_VERSION_MAJOR < 4
 #include "301/CO_driver.h"
 #include "CO_OD.h"
 #include "301/CO_SDOserver.h"
#else
 #error This Object dictionary is not compatible with CANopenNode v4.0 and up!
#endif

/*******************************************************************************
   DEFINITION AND INITIALIZATION OF OBJECT DICTIONARY VARIABLES
*******************************************************************************/


/***** Definition for RAM variables *******************************************/
struct sCO_OD_RAM CO_OD_RAM = {
           CO_OD_FIRST_LAST_WORD,

/*1001*/ 0x0L,
/*1002*/ 0x0000L,
/*1003*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1010*/ {0x0001L, 0x0001L, 0x0001L, 0x0001L},
/*1011*/ {0x0001L, 0x0001L, 0x0001L, 0x0001L},
/*1023*/ {0x3L, 0, 0x0L, 0},
/*1025*/ {0x3L, 0, 0x0L, 0},
/*1026*/ {0x0L, 0x0L, 0x0L},
/*2010*/ 0x00000000L,
/*2011*/ 0x00000000L,
/*2100*/ {0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},
/*2101*/ 0x10L,
/*3000*/ {0x1CL, 0, 0, 0, 0, 0x0000L, 0x0L, 0, 0x0L, 0x00, 0x0L, 0x0L, 0, 0, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0L, 0x0000L, 0x0000L, 0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0L},
/*3001*/ {0x9L, 0x0L, 0x0L, 0x0L, 0, 0x0000L, 0x0000L, 0, 0x0000L, 0},
/*3002*/ {0x4L, 0, 0, 0, 0},
/*3003*/ {0x3L, 0, 0, 0},
/*3005*/ {0x4L, 0x0L, 0x0L, 0, 0x0},
/*3006*/ 0x0L,
/*30F0*/ {0x9L, 0x0000L, 0x0000L, 0, 0, 0, 0, 0, 0, 0},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for ROM variables *******************************************/
struct sCO_OD_ROM CO_OD_ROM = {
           CO_OD_FIRST_LAST_WORD,

/*1000*/ 0x0000L,
/*1008*/ {'O', 'r', 'e', 'S', 'a', 't', ' ', 'L', 'i', 'n', 'u', 'x', ' ', 'G', 'e', 'n', 'e', 'r', 'i', 'c'},
/*1009*/ {'0', '.', '0'},
/*100A*/ {'0', '.', '0', '.', '0'},
/*1018*/ {0x4L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for EEPROM variables *******************************************/
struct sCO_OD_EEPROM CO_OD_EEPROM = {
           CO_OD_FIRST_LAST_WORD,


           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for PERSIST_COMM variables *******************************************/
struct sCO_OD_PERSIST_COMM CO_OD_PERSIST_COMM = {
           CO_OD_FIRST_LAST_WORD,

/*1005*/ 0x0080L,
/*1006*/ 0x0000L,
/*1007*/ 0x0000L,
/*1014*/ 0x0080L,
/*1015*/ 0x00,
/*1016*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1017*/ 0x3E8,
/*1019*/ 0x0L,
/*1024*/ 0x0L,
/*1029*/ {0x0L, 0x0L},
/*1200*/ {{0x3L, 0x80000000L, 0x80000000L, 0x1L}},
/*1400*/ {{0x5L, 0x80000200L, 0xFEL, 0x00},
/*1401*/ {0x5L, 0x80000300L, 0xFEL, 0x00},
/*1402*/ {0x5L, 0x80000400L, 0xFEL, 0x00},
/*1403*/ {0x5L, 0x80000500L, 0xFEL, 0x00}},
/*1600*/ {{0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1601*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1602*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1603*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1800*/ {{0x6L, 0xC0000180L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1801*/ {0x6L, 0xC0000280L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1802*/ {0x6L, 0xC0000380L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1803*/ {0x6L, 0xC0000480L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L}},
/*1A00*/ {{0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A01*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A02*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A03*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1F80*/ 0x0008L,

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for PERSIST_MFR variables *******************************************/
struct sCO_OD_PERSIST_MFR CO_OD_PERSIST_MFR = {
           CO_OD_FIRST_LAST_WORD,

/*2000*/ {0x4L, 0x0L, 0x0L, 0x0L, 0x0L},

           CO_OD_FIRST_LAST_WORD,
};




/*******************************************************************************
   STRUCTURES FOR RECORD TYPE OBJECTS
*******************************************************************************/


/*0x1018*/ const CO_OD_entryRecord_t OD_record1018[5] = {
           {(void*)&CO_OD_ROM.identity.highestSubIndexSupported, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.identity.vendorID, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.identity.productCode, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.identity.revisionNumber, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.identity.serialNumber, 0x85, 0x4 },
};

/*0x1023*/ const CO_OD_entryRecord_t OD_record1023[4] = {
           {(void*)&CO_OD_RAM.OSCommand.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)0, 0x0E, 0x0 },
           {(void*)&CO_OD_RAM.OSCommand.status, 0x06, 0x1 },
           {(void*)0, 0x06, 0x0 },
};

/*0x1025*/ const CO_OD_entryRecord_t OD_record1025[4] = {
           {(void*)&CO_OD_RAM.OSDebuggerInterface.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)0, 0x0E, 0x0 },
           {(void*)&CO_OD_RAM.OSDebuggerInterface.status, 0x06, 0x1 },
           {(void*)0, 0x06, 0x0 },
};

/*0x1200*/ const CO_OD_entryRecord_t OD_record1200[4] = {
           {(void*)&CO_OD_PERSIST_COMM.SDOServerParameter[0].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.SDOServerParameter[0].COB_IDClientToServer, 0xBF, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.SDOServerParameter[0].COB_IDServerToClient, 0xBF, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.SDOServerParameter[0].nodeIDOfTheSDOClient, 0x0F, 0x1 },
};

/*0x1400*/ const CO_OD_entryRecord_t OD_record1400[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[0].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[0].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[0].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[0].eventTimer, 0x8F, 0x2 },
};

/*0x1401*/ const CO_OD_entryRecord_t OD_record1401[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[1].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[1].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[1].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[1].eventTimer, 0x8F, 0x2 },
};

/*0x1402*/ const CO_OD_entryRecord_t OD_record1402[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[2].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[2].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[2].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[2].eventTimer, 0x8F, 0x2 },
};

/*0x1403*/ const CO_OD_entryRecord_t OD_record1403[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[3].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[3].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[3].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[3].eventTimer, 0x8F, 0x2 },
};

/*0x1600*/ const CO_OD_entryRecord_t OD_record1600[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].mappingObject8, 0x8F, 0x4 },
};

/*0x1601*/ const CO_OD_entryRecord_t OD_record1601[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].mappingObject8, 0x8F, 0x4 },
};

/*0x1602*/ const CO_OD_entryRecord_t OD_record1602[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].mappingObject8, 0x8F, 0x4 },
};

/*0x1603*/ const CO_OD_entryRecord_t OD_record1603[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].mappingObject8, 0x8F, 0x4 },
};

/*0x1800*/ const CO_OD_entryRecord_t OD_record1800[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1801*/ const CO_OD_entryRecord_t OD_record1801[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1802*/ const CO_OD_entryRecord_t OD_record1802[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1803*/ const CO_OD_entryRecord_t OD_record1803[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1A00*/ const CO_OD_entryRecord_t OD_record1A00[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].mappingObject8, 0x8F, 0x4 },
};

/*0x1A01*/ const CO_OD_entryRecord_t OD_record1A01[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].mappingObject8, 0x8F, 0x4 },
};

/*0x1A02*/ const CO_OD_entryRecord_t OD_record1A02[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].mappingObject8, 0x8F, 0x4 },
};

/*0x1A03*/ const CO_OD_entryRecord_t OD_record1A03[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].mappingObject8, 0x8F, 0x4 },
};

/*0x2000*/ const CO_OD_entryRecord_t OD_record2000[5] = {
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.bdefault, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.ttoggle, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.ntoggle, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.ctoggle, 0x0F, 0x1 },
};

/*0x3000*/ const CO_OD_entryRecord_t OD_record3000[29] = {
           {(void*)&CO_OD_RAM.boardInfo.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.boardInfo.uptime, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.numberOfCPUs, 0x06, 0x1 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.boardInfo.CPUGovernor, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.boardInfo.CPUFrequency, 0x86, 0x2 },
           {(void*)&CO_OD_RAM.boardInfo.numberOfRemoteprocs, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.boardInfo.remoteprocXSelector, 0x0E, 0x1 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.boardInfo.loadAverage1min, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.loadAverage5min, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.loadAverage15min, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.ramTotal, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.ramFree, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.ramShared, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.ramBuffered, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.ramPercent, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.boardInfo.swapTotal, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.swapFree, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.swapPercent, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.boardInfo.procs, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.rootParitionTotal, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.rootParitionFree, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.boardInfo.rootParitionPercent, 0x26, 0x1 },
};

/*0x3001*/ const CO_OD_entryRecord_t OD_record3001[10] = {
           {(void*)&CO_OD_RAM.fileCaches.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.fileCaches.freadCacheLen, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.fileCaches.fwriteCacheLen, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.fileCaches.cacheSelector, 0x0E, 0x1 },
           {(void*)0, 0x0E, 0x0 },
           {(void*)&CO_OD_RAM.fileCaches.cacheLen, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.fileCaches.iterator, 0x8E, 0x4 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.fileCaches.fileSize, 0x86, 0x4 },
           {(void*)0, 0x0A, 0x0 },
};

/*0x3002*/ const CO_OD_entryRecord_t OD_record3002[5] = {
           {(void*)&CO_OD_RAM.fread.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)0, 0x0E, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)0, 0x0A, 0x0 },
};

/*0x3003*/ const CO_OD_entryRecord_t OD_record3003[4] = {
           {(void*)&CO_OD_RAM.fwrite.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)0, 0x0E, 0x0 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)0, 0x0A, 0x0 },
};

/*0x3005*/ const CO_OD_entryRecord_t OD_record3005[5] = {
           {(void*)&CO_OD_RAM.appManager.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.appManager.totalApps, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.appManager.selectApp, 0x0E, 0x1 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.appManager.daemonState, 0x0E, 0x1 },
};

/*0x30F0*/ const CO_OD_entryRecord_t OD_record30F0[10] = {
           {(void*)&CO_OD_RAM.linuxUpdaterApp.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.linuxUpdaterApp.currentState, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.linuxUpdaterApp.updatesAvailable, 0x86, 0x4 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)0, 0x0A, 0x0 },
};

/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
const CO_OD_entry_t CO_OD[CO_OD_NoOfElements] = {
{0x1000, 0x00, 0x85,  4, (void*)&CO_OD_ROM.deviceType},
{0x1001, 0x00, 0x36,  1, (void*)&CO_OD_RAM.errorRegister},
{0x1002, 0x00, 0xB6,  4, (void*)&CO_OD_RAM.manufacturerStatusRegister},
{0x1003, 0x08, 0x8E,  4, (void*)&CO_OD_RAM.preDefinedErrorField[0]},
{0x1005, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.COB_ID_SYNCMessage},
{0x1006, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.communicationCyclePeriod},
{0x1007, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.synchronousWindowLength},
{0x1008, 0x00, 0x05, 20, (void*)&CO_OD_ROM.manufacturerDeviceName},
{0x1009, 0x00, 0x05,  3, (void*)&CO_OD_ROM.manufacturerHardwareVersion},
{0x100A, 0x00, 0x05,  5, (void*)&CO_OD_ROM.manufacturerSoftwareVersion},
{0x1010, 0x04, 0x8E,  4, (void*)&CO_OD_RAM.storeParameters[0]},
{0x1011, 0x04, 0x8E,  4, (void*)&CO_OD_RAM.restoreDefaultParameters[0]},
{0x1014, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.COB_ID_EMCY},
{0x1015, 0x00, 0x8F,  2, (void*)&CO_OD_PERSIST_COMM.inhibitTimeEMCY},
{0x1016, 0x08, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.consumerHeartbeatTime[0]},
{0x1017, 0x00, 0x8F,  2, (void*)&CO_OD_PERSIST_COMM.producerHeartbeatTime},
{0x1018, 0x04, 0x00,  0, (void*)&OD_record1018},
{0x1019, 0x00, 0x0F,  1, (void*)&CO_OD_PERSIST_COMM.synchronousCounterOverflowValue},
{0x1023, 0x03, 0x00,  0, (void*)&OD_record1023},
{0x1024, 0x00, 0x0B,  1, (void*)&CO_OD_PERSIST_COMM.OSCommandMode},
{0x1025, 0x03, 0x00,  0, (void*)&OD_record1025},
{0x1026, 0x03, 0x3E,  1, (void*)&CO_OD_RAM.OSPrompt[0]},
{0x1029, 0x02, 0x0F,  1, (void*)&CO_OD_PERSIST_COMM.errorBehavior[0]},
{0x1200, 0x03, 0x00,  0, (void*)&OD_record1200},
{0x1400, 0x03, 0x00,  0, (void*)&OD_record1400},
{0x1401, 0x03, 0x00,  0, (void*)&OD_record1401},
{0x1402, 0x03, 0x00,  0, (void*)&OD_record1402},
{0x1403, 0x03, 0x00,  0, (void*)&OD_record1403},
{0x1600, 0x08, 0x00,  0, (void*)&OD_record1600},
{0x1601, 0x08, 0x00,  0, (void*)&OD_record1601},
{0x1602, 0x08, 0x00,  0, (void*)&OD_record1602},
{0x1603, 0x08, 0x00,  0, (void*)&OD_record1603},
{0x1800, 0x06, 0x00,  0, (void*)&OD_record1800},
{0x1801, 0x06, 0x00,  0, (void*)&OD_record1801},
{0x1802, 0x06, 0x00,  0, (void*)&OD_record1802},
{0x1803, 0x06, 0x00,  0, (void*)&OD_record1803},
{0x1A00, 0x08, 0x00,  0, (void*)&OD_record1A00},
{0x1A01, 0x08, 0x00,  0, (void*)&OD_record1A01},
{0x1A02, 0x08, 0x00,  0, (void*)&OD_record1A02},
{0x1A03, 0x08, 0x00,  0, (void*)&OD_record1A03},
{0x1F80, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.NMTStartup},
{0x2000, 0x04, 0x00,  0, (void*)&OD_record2000},
{0x2010, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.SCET},
{0x2011, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.UTC},
{0x2100, 0x00, 0x06, 10, (void*)&CO_OD_RAM.errorStatusBits},
{0x2101, 0x00, 0x0E,  1, (void*)&CO_OD_RAM.CANNodeID},
{0x3000, 0x1C, 0x00,  0, (void*)&OD_record3000},
{0x3001, 0x09, 0x00,  0, (void*)&OD_record3001},
{0x3002, 0x04, 0x00,  0, (void*)&OD_record3002},
{0x3003, 0x03, 0x00,  0, (void*)&OD_record3003},
{0x3005, 0x04, 0x00,  0, (void*)&OD_record3005},
{0x3006, 0x00, 0x06,  1, (void*)&CO_OD_RAM.getLog},
{0x30F0, 0x09, 0x00,  0, (void*)&OD_record30F0},
};
// clang-format on

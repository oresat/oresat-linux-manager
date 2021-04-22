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
/*2010*/ 0x00000000L,
/*2011*/ 0x00000000L,
/*2100*/ {0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},
/*3000*/ {0x4L, 0, 0, 0, 0},
/*3001*/ {0x1CL, 0, 0, 0, 0, 0x0000L, 0x0L, 0, 0x0L, 0x00, 0x0L, 0x0L, 0, 0, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0L, 0x0000L, 0x0000L, 0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0L},
/*3002*/ {0x9L, 0x0L, 0x0L, 0x0L, 0, 0x0000L, 0x0000L, 0, 0x0000L, 0},
/*3003*/ {0x4L, 0, 0, 0, 0},
/*3004*/ {0x3L, 0, 0, 0},
/*3005*/ {0x6L, 0x0L, 0x0L, 0x0L, 0x0L, 0, 0x0L},
/*3006*/ 0x0L,
/*3100*/ {0x5L, 0xFFL, 0x0L, 0, 0, 0},
/*6000*/ 0xFFL,
/*6001*/ 0x0L,
/*6002*/ {0x7L, 0x00000000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*6003*/ 0,

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for ROM variables *******************************************/
struct sCO_OD_ROM CO_OD_ROM = {
           CO_OD_FIRST_LAST_WORD,

/*1000*/ 0x0000L,
/*1008*/ {'O', 'r', 'e', 'S', 'a', 't', ' ', 'G', 'P', 'S'},
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
/*1029*/ {0x0L, 0x0L},
/*1200*/ {{0x3L, 0x80000000L, 0x80000000L, 0x1L}},
/*1400*/ {{0x5L, 0x04B3L, 0xFEL, 0x00},
/*1401*/ {0x5L, 0x80000300L, 0xFEL, 0x00},
/*1402*/ {0x5L, 0x80000400L, 0xFEL, 0x00},
/*1403*/ {0x5L, 0x80000500L, 0xFEL, 0x00},
/*1404*/ {0x5L, 0x80000201L, 0xFEL, 0x00},
/*1405*/ {0x5L, 0x80000301L, 0xFEL, 0x00},
/*1406*/ {0x5L, 0x80000401L, 0xFEL, 0x00},
/*1407*/ {0x5L, 0x80000501L, 0xFEL, 0x00},
/*1408*/ {0x5L, 0x80000202L, 0xFEL, 0x00},
/*1409*/ {0x5L, 0x80000302L, 0xFEL, 0x00},
/*140A*/ {0x5L, 0x80000402L, 0xFEL, 0x00},
/*140B*/ {0x5L, 0x80000502L, 0xFEL, 0x00},
/*140C*/ {0x5L, 0x80000203L, 0xFEL, 0x00},
/*140D*/ {0x5L, 0x80000303L, 0xFEL, 0x00},
/*140E*/ {0x5L, 0x80000403L, 0xFEL, 0x00},
/*140F*/ {0x5L, 0x80000503L, 0xFEL, 0x00}},
/*1600*/ {{0x1L, 0x20100040L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1601*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1602*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1603*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1604*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1605*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1606*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1607*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1608*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1609*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160A*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160B*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160C*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160D*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160E*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160F*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1800*/ {{0x6L, 0x40000180L, 0xFEL, 0x00, 0x0L, 0x7530, 0x0L},
/*1801*/ {0x6L, 0x40000280L, 0xFEL, 0x00, 0x0L, 0x3E8, 0x0L},
/*1802*/ {0x6L, 0x40000380L, 0xFEL, 0x00, 0x0L, 0x3E8, 0x0L},
/*1803*/ {0x6L, 0x40000480L, 0xFEL, 0x00, 0x0L, 0x3E8, 0x0L},
/*1804*/ {0x6L, 0x40000181L, 0xFEL, 0x00, 0x0L, 0x3E8, 0x0L},
/*1805*/ {0x6L, 0x40000281L, 0xFEL, 0x00, 0x0L, 0x3E8, 0x0L},
/*1806*/ {0x6L, 0xC0000381L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1807*/ {0x6L, 0xC0000481L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1808*/ {0x6L, 0xC0000182L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1809*/ {0x6L, 0xC0000282L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180A*/ {0x6L, 0xC0000382L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180B*/ {0x6L, 0xC0000482L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180C*/ {0x6L, 0xC0000183L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180D*/ {0x6L, 0xC0000283L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180E*/ {0x6L, 0xC0000383L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180F*/ {0x6L, 0x40000483L, 0x0L, 0x00, 0x0L, 0x01, 0x0L}},
/*1A00*/ {{0x6L, 0x30011C08L, 0x30011508L, 0x30020108L, 0x30020208L, 0x30050208L, 0x30050308L, 0x0000L, 0x0000L},
/*1A01*/ {0x2L, 0x31000108L, 0x31000208L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A02*/ {0x1L, 0x60020140L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A03*/ {0x2L, 0x60020220L, 0x60020320L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A04*/ {0x2L, 0x60020420L, 0x60020520L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A05*/ {0x2L, 0x60020620L, 0x60020720L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A06*/ {0x2L, 0x60000008L, 0x60010008L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A07*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A08*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A09*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0A*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0B*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0C*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0D*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0E*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0F*/ {0x1L, 0x20100040L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
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

/*0x1404*/ const CO_OD_entryRecord_t OD_record1404[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[4].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[4].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[4].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[4].eventTimer, 0x8F, 0x2 },
};

/*0x1405*/ const CO_OD_entryRecord_t OD_record1405[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[5].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[5].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[5].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[5].eventTimer, 0x8F, 0x2 },
};

/*0x1406*/ const CO_OD_entryRecord_t OD_record1406[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[6].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[6].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[6].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[6].eventTimer, 0x8F, 0x2 },
};

/*0x1407*/ const CO_OD_entryRecord_t OD_record1407[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[7].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[7].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[7].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[7].eventTimer, 0x8F, 0x2 },
};

/*0x1408*/ const CO_OD_entryRecord_t OD_record1408[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[8].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[8].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[8].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[8].eventTimer, 0x8F, 0x2 },
};

/*0x1409*/ const CO_OD_entryRecord_t OD_record1409[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[9].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[9].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[9].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[9].eventTimer, 0x8F, 0x2 },
};

/*0x140A*/ const CO_OD_entryRecord_t OD_record140A[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[10].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[10].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[10].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[10].eventTimer, 0x8F, 0x2 },
};

/*0x140B*/ const CO_OD_entryRecord_t OD_record140B[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[11].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[11].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[11].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[11].eventTimer, 0x8F, 0x2 },
};

/*0x140C*/ const CO_OD_entryRecord_t OD_record140C[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[12].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[12].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[12].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[12].eventTimer, 0x8F, 0x2 },
};

/*0x140D*/ const CO_OD_entryRecord_t OD_record140D[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[13].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[13].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[13].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[13].eventTimer, 0x8F, 0x2 },
};

/*0x140E*/ const CO_OD_entryRecord_t OD_record140E[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[14].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[14].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[14].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[14].eventTimer, 0x8F, 0x2 },
};

/*0x140F*/ const CO_OD_entryRecord_t OD_record140F[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[15].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[15].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[15].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[15].eventTimer, 0x8F, 0x2 },
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

/*0x1604*/ const CO_OD_entryRecord_t OD_record1604[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].mappingObject8, 0x8F, 0x4 },
};

/*0x1605*/ const CO_OD_entryRecord_t OD_record1605[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].mappingObject8, 0x8F, 0x4 },
};

/*0x1606*/ const CO_OD_entryRecord_t OD_record1606[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].mappingObject8, 0x8F, 0x4 },
};

/*0x1607*/ const CO_OD_entryRecord_t OD_record1607[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].mappingObject8, 0x8F, 0x4 },
};

/*0x1608*/ const CO_OD_entryRecord_t OD_record1608[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].mappingObject8, 0x8F, 0x4 },
};

/*0x1609*/ const CO_OD_entryRecord_t OD_record1609[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].mappingObject8, 0x8F, 0x4 },
};

/*0x160A*/ const CO_OD_entryRecord_t OD_record160A[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].mappingObject8, 0x8F, 0x4 },
};

/*0x160B*/ const CO_OD_entryRecord_t OD_record160B[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].mappingObject8, 0x8F, 0x4 },
};

/*0x160C*/ const CO_OD_entryRecord_t OD_record160C[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].mappingObject8, 0x8F, 0x4 },
};

/*0x160D*/ const CO_OD_entryRecord_t OD_record160D[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].mappingObject8, 0x8F, 0x4 },
};

/*0x160E*/ const CO_OD_entryRecord_t OD_record160E[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].mappingObject8, 0x8F, 0x4 },
};

/*0x160F*/ const CO_OD_entryRecord_t OD_record160F[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].mappingObject8, 0x8F, 0x4 },
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

/*0x1804*/ const CO_OD_entryRecord_t OD_record1804[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1805*/ const CO_OD_entryRecord_t OD_record1805[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1806*/ const CO_OD_entryRecord_t OD_record1806[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1807*/ const CO_OD_entryRecord_t OD_record1807[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1808*/ const CO_OD_entryRecord_t OD_record1808[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1809*/ const CO_OD_entryRecord_t OD_record1809[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180A*/ const CO_OD_entryRecord_t OD_record180A[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180B*/ const CO_OD_entryRecord_t OD_record180B[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180C*/ const CO_OD_entryRecord_t OD_record180C[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180D*/ const CO_OD_entryRecord_t OD_record180D[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180E*/ const CO_OD_entryRecord_t OD_record180E[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180F*/ const CO_OD_entryRecord_t OD_record180F[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].SYNCStartValue, 0x0F, 0x1 },
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

/*0x1A04*/ const CO_OD_entryRecord_t OD_record1A04[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].mappingObject8, 0x8F, 0x4 },
};

/*0x1A05*/ const CO_OD_entryRecord_t OD_record1A05[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].mappingObject8, 0x8F, 0x4 },
};

/*0x1A06*/ const CO_OD_entryRecord_t OD_record1A06[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].mappingObject8, 0x8F, 0x4 },
};

/*0x1A07*/ const CO_OD_entryRecord_t OD_record1A07[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].mappingObject8, 0x8F, 0x4 },
};

/*0x1A08*/ const CO_OD_entryRecord_t OD_record1A08[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].mappingObject8, 0x8F, 0x4 },
};

/*0x1A09*/ const CO_OD_entryRecord_t OD_record1A09[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].mappingObject8, 0x8F, 0x4 },
};

/*0x1A0A*/ const CO_OD_entryRecord_t OD_record1A0A[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].mappingObject8, 0x8F, 0x4 },
};

/*0x1A0B*/ const CO_OD_entryRecord_t OD_record1A0B[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].mappingObject8, 0x8F, 0x4 },
};

/*0x1A0C*/ const CO_OD_entryRecord_t OD_record1A0C[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].mappingObject8, 0x8F, 0x4 },
};

/*0x1A0D*/ const CO_OD_entryRecord_t OD_record1A0D[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].mappingObject8, 0x8F, 0x4 },
};

/*0x1A0E*/ const CO_OD_entryRecord_t OD_record1A0E[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].mappingObject8, 0x8F, 0x4 },
};

/*0x1A0F*/ const CO_OD_entryRecord_t OD_record1A0F[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].mappingObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].mappingObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].mappingObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].mappingObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].mappingObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].mappingObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].mappingObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].mappingObject8, 0x8F, 0x4 },
};

/*0x2000*/ const CO_OD_entryRecord_t OD_record2000[5] = {
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.bdefault, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.ttoggle, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.ntoggle, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUSManagement.ctoggle, 0x0F, 0x1 },
};

/*0x3000*/ const CO_OD_entryRecord_t OD_record3000[5] = {
           {(void*)&CO_OD_RAM.OLMControl.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)&CO_OD_RAM.OLMControl.quit, 0x0A, 0x1 },
           {(void*)&CO_OD_RAM.OLMControl.CPUFrequency, 0x0E, 0x1 },
};

/*0x3001*/ const CO_OD_entryRecord_t OD_record3001[29] = {
           {(void*)&CO_OD_RAM.systemInfo.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.systemInfo.uptime, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.numberOfCPUs, 0x06, 0x1 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.systemInfo.CPUGovernor, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.systemInfo.CPUFrequency, 0x86, 0x2 },
           {(void*)&CO_OD_RAM.systemInfo.numberOfRemoteprocs, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.systemInfo.remoteprocXSelector, 0x0E, 0x1 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.systemInfo.loadAverage1min, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.loadAverage5min, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.loadAverage15min, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.ramTotal, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.ramFree, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.ramShared, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.ramBuffered, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.ramPercent, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.systemInfo.swapTotal, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.swapFree, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.swapPercent, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.systemInfo.procs, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.rootParitionTotal, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.rootParitionFree, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.systemInfo.rootParitionPercent, 0x26, 0x1 },
};

/*0x3002*/ const CO_OD_entryRecord_t OD_record3002[10] = {
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

/*0x3003*/ const CO_OD_entryRecord_t OD_record3003[5] = {
           {(void*)&CO_OD_RAM.fread.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)0, 0x0E, 0x0 },
           {(void*)0, 0x06, 0x0 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)0, 0x0A, 0x0 },
};

/*0x3004*/ const CO_OD_entryRecord_t OD_record3004[4] = {
           {(void*)&CO_OD_RAM.fwrite.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)0, 0x0E, 0x0 },
           {(void*)0, 0x0A, 0x0 },
           {(void*)0, 0x0A, 0x0 },
};

/*0x3005*/ const CO_OD_entryRecord_t OD_record3005[7] = {
           {(void*)&CO_OD_RAM.appManager.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.appManager.totalApps, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.appManager.activeApps, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.appManager.failedApps, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.appManager.selectApp, 0x0E, 0x1 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.appManager.daemonState, 0x0E, 0x1 },
};

/*0x3100*/ const CO_OD_entryRecord_t OD_record3100[6] = {
           {(void*)&CO_OD_RAM.updater.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.updater.status, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.updater.updatesAvailable, 0x26, 0x1 },
           {(void*)0, 0x06, 0x0 },
           {(void*)&CO_OD_RAM.updater.update, 0x0A, 0x1 },
           {(void*)&CO_OD_RAM.updater.makeStatusFile, 0x0A, 0x1 },
};

/*0x6002*/ const CO_OD_entryRecord_t OD_record6002[8] = {
           {(void*)&CO_OD_RAM.stateVector.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.stateVector.timeStamp, 0xA6, 0x8 },
           {(void*)&CO_OD_RAM.stateVector.positionX, 0xA6, 0x4 },
           {(void*)&CO_OD_RAM.stateVector.positionY, 0xA6, 0x4 },
           {(void*)&CO_OD_RAM.stateVector.positionZ, 0xA6, 0x4 },
           {(void*)&CO_OD_RAM.stateVector.velocityX, 0xA6, 0x4 },
           {(void*)&CO_OD_RAM.stateVector.velocityY, 0xA6, 0x4 },
           {(void*)&CO_OD_RAM.stateVector.velocityZ, 0xA6, 0x4 },
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
{0x1008, 0x00, 0x05, 10, (void*)&CO_OD_ROM.manufacturerDeviceName},
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
{0x1029, 0x02, 0x0F,  1, (void*)&CO_OD_PERSIST_COMM.errorBehavior[0]},
{0x1200, 0x03, 0x00,  0, (void*)&OD_record1200},
{0x1400, 0x03, 0x00,  0, (void*)&OD_record1400},
{0x1401, 0x03, 0x00,  0, (void*)&OD_record1401},
{0x1402, 0x03, 0x00,  0, (void*)&OD_record1402},
{0x1403, 0x03, 0x00,  0, (void*)&OD_record1403},
{0x1404, 0x03, 0x00,  0, (void*)&OD_record1404},
{0x1405, 0x03, 0x00,  0, (void*)&OD_record1405},
{0x1406, 0x03, 0x00,  0, (void*)&OD_record1406},
{0x1407, 0x03, 0x00,  0, (void*)&OD_record1407},
{0x1408, 0x03, 0x00,  0, (void*)&OD_record1408},
{0x1409, 0x03, 0x00,  0, (void*)&OD_record1409},
{0x140A, 0x03, 0x00,  0, (void*)&OD_record140A},
{0x140B, 0x03, 0x00,  0, (void*)&OD_record140B},
{0x140C, 0x03, 0x00,  0, (void*)&OD_record140C},
{0x140D, 0x03, 0x00,  0, (void*)&OD_record140D},
{0x140E, 0x03, 0x00,  0, (void*)&OD_record140E},
{0x140F, 0x03, 0x00,  0, (void*)&OD_record140F},
{0x1600, 0x08, 0x00,  0, (void*)&OD_record1600},
{0x1601, 0x08, 0x00,  0, (void*)&OD_record1601},
{0x1602, 0x08, 0x00,  0, (void*)&OD_record1602},
{0x1603, 0x08, 0x00,  0, (void*)&OD_record1603},
{0x1604, 0x08, 0x00,  0, (void*)&OD_record1604},
{0x1605, 0x08, 0x00,  0, (void*)&OD_record1605},
{0x1606, 0x08, 0x00,  0, (void*)&OD_record1606},
{0x1607, 0x08, 0x00,  0, (void*)&OD_record1607},
{0x1608, 0x08, 0x00,  0, (void*)&OD_record1608},
{0x1609, 0x08, 0x00,  0, (void*)&OD_record1609},
{0x160A, 0x08, 0x00,  0, (void*)&OD_record160A},
{0x160B, 0x08, 0x00,  0, (void*)&OD_record160B},
{0x160C, 0x08, 0x00,  0, (void*)&OD_record160C},
{0x160D, 0x08, 0x00,  0, (void*)&OD_record160D},
{0x160E, 0x08, 0x00,  0, (void*)&OD_record160E},
{0x160F, 0x08, 0x00,  0, (void*)&OD_record160F},
{0x1800, 0x06, 0x00,  0, (void*)&OD_record1800},
{0x1801, 0x06, 0x00,  0, (void*)&OD_record1801},
{0x1802, 0x06, 0x00,  0, (void*)&OD_record1802},
{0x1803, 0x06, 0x00,  0, (void*)&OD_record1803},
{0x1804, 0x06, 0x00,  0, (void*)&OD_record1804},
{0x1805, 0x06, 0x00,  0, (void*)&OD_record1805},
{0x1806, 0x06, 0x00,  0, (void*)&OD_record1806},
{0x1807, 0x06, 0x00,  0, (void*)&OD_record1807},
{0x1808, 0x06, 0x00,  0, (void*)&OD_record1808},
{0x1809, 0x06, 0x00,  0, (void*)&OD_record1809},
{0x180A, 0x06, 0x00,  0, (void*)&OD_record180A},
{0x180B, 0x06, 0x00,  0, (void*)&OD_record180B},
{0x180C, 0x06, 0x00,  0, (void*)&OD_record180C},
{0x180D, 0x06, 0x00,  0, (void*)&OD_record180D},
{0x180E, 0x06, 0x00,  0, (void*)&OD_record180E},
{0x180F, 0x06, 0x00,  0, (void*)&OD_record180F},
{0x1A00, 0x08, 0x00,  0, (void*)&OD_record1A00},
{0x1A01, 0x08, 0x00,  0, (void*)&OD_record1A01},
{0x1A02, 0x08, 0x00,  0, (void*)&OD_record1A02},
{0x1A03, 0x08, 0x00,  0, (void*)&OD_record1A03},
{0x1A04, 0x08, 0x00,  0, (void*)&OD_record1A04},
{0x1A05, 0x08, 0x00,  0, (void*)&OD_record1A05},
{0x1A06, 0x08, 0x00,  0, (void*)&OD_record1A06},
{0x1A07, 0x08, 0x00,  0, (void*)&OD_record1A07},
{0x1A08, 0x08, 0x00,  0, (void*)&OD_record1A08},
{0x1A09, 0x08, 0x00,  0, (void*)&OD_record1A09},
{0x1A0A, 0x08, 0x00,  0, (void*)&OD_record1A0A},
{0x1A0B, 0x08, 0x00,  0, (void*)&OD_record1A0B},
{0x1A0C, 0x08, 0x00,  0, (void*)&OD_record1A0C},
{0x1A0D, 0x08, 0x00,  0, (void*)&OD_record1A0D},
{0x1A0E, 0x08, 0x00,  0, (void*)&OD_record1A0E},
{0x1A0F, 0x08, 0x00,  0, (void*)&OD_record1A0F},
{0x1F80, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.NMTStartup},
{0x2000, 0x04, 0x00,  0, (void*)&OD_record2000},
{0x2010, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.SCET},
{0x2011, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.UTC},
{0x2100, 0x00, 0x06, 10, (void*)&CO_OD_RAM.errorStatusBits},
{0x3000, 0x04, 0x00,  0, (void*)&OD_record3000},
{0x3001, 0x1C, 0x00,  0, (void*)&OD_record3001},
{0x3002, 0x09, 0x00,  0, (void*)&OD_record3002},
{0x3003, 0x04, 0x00,  0, (void*)&OD_record3003},
{0x3004, 0x03, 0x00,  0, (void*)&OD_record3004},
{0x3005, 0x06, 0x00,  0, (void*)&OD_record3005},
{0x3006, 0x00, 0x0E,  1, (void*)&CO_OD_RAM.getLog},
{0x3100, 0x05, 0x00,  0, (void*)&OD_record3100},
{0x6000, 0x00, 0x26,  1, (void*)&CO_OD_RAM.GPSStatus},
{0x6001, 0x00, 0x26,  1, (void*)&CO_OD_RAM.satellitesLocked},
{0x6002, 0x07, 0x00,  0, (void*)&OD_record6002},
{0x6003, 0x00, 0x26,  1, (void*)&CO_OD_RAM.timeSynchronized},
};
// clang-format on

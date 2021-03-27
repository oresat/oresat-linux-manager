CANopen device documentation
============================
**OreSat Generic**

OreSat Generic

|              |                                |
| ------------ | ------------------------------ |
| Project File | generic_OD.xdd                 |
| File Version | 1                              |
| Created      | 3/9/2021 11:41:40 PM           |
| Created By   | Ryan Medick                    |
| Modified     | 3/25/2021 11:00:43 PM          |
| Modified By  | Ryan Medick                    |

This file was automatically generated with [libedssharp](https://github.com/robincornelius/libedssharp) Object Dictionary Editor v0.8-123-g6c02323

* [Device Information](#device-information)
* [PDO Mapping](#pdo-mapping)
* [Communication Specific Parameters](#communication-specific-parameters)
* [Manufacturer Specific Parameters](#manufacturer-specific-parameters)
* [Device Profile Specific Parameters](#device-profile-specific-parameters)


Device Information {#device-information}
----------------------------------------
|              |                                |
| ------------ | ------------------------------ |
| Vendor Name  | Portland State Aerospace Society |
| Vendor ID    | 0                              |
| Product Name | OreSat Generic                 |
| Product ID   | 0                              |
| Granularity  | 8                              |
| RPDO count   | 4                              |
| TPDO count   | 4                              |
| LSS Slave    | False                          |
| LSS Master   | False                          |

#### Supported Baud rates
* [x] 10 kBit/s
* [x] 20 kBit/s
* [x] 50 kBit/s
* [x] 125 kBit/s
* [x] 250 kBit/s
* [x] 500 kBit/s
* [x] 800 kBit/s
* [x] 1000 kBit/s
* [ ] auto


PDO Mapping {#pdo-mapping}
--------------------------

Communication Specific Parameters {#communication-specific-parameters}
----------------------------------------------------------------------

### 0x1000 - Device type
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         | NMT            | ROM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED32              | ro  | no  | no   | 0x00000000                      |

* bit 16-31: Additional information
* bit 0-15: Device profile number

### 0x1001 - Error register
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         | EM             | RAM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED8               | ro  | tr  | no   | 0x00                            |

* bit 7: manufacturer specific
* bit 6: Reserved (always 0)
* bit 5: device profile specific
* bit 4: communication error (overrun, error state)
* bit 3: temperature
* bit 2: voltage
* bit 1: current
* bit 0: generic error

### 0x1002 - Manufacturer status register
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | RAM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED32              | ro  | tr  | no   | 0                               |

### 0x1003 - Pre-defined error field
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| ARRAY       |                | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Number of errors      | UNSIGNED8  | rw  | no  | no   | 0             |
| 0x01 | Standard error field  | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x02 | Standard error field  | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x03 | Standard error field  | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x04 | Standard error field  | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x05 | Standard error field  | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x06 | Standard error field  | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x07 | Standard error field  | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x08 | Standard error field  | UNSIGNED32 | ro  | no  | no   | 0x00000000    |

* Sub Index 0: Contains number of actual errors. 0 can be written to clear error history.
* sub-index 1 and above:
  * bit 16-31: Manufacturer specific additional information
  * bit 0-15: Error code as transmited in the Emergency object

### 0x1005 - COB-ID SYNC message
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         | SYNC           | PERSIST_COMM   |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED32              | rw  | no  | no   | 0x00000080                      |

* bit 31: set to 0
* bit 30: If set, CANopen device generates SYNC object
* bit 11-29: set to 0
* bit 0-10: 11-bit CAN-ID

### 0x1006 - Communication cycle period
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         | SYNC_PROD      | PERSIST_COMM   |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED32              | rw  | no  | no   | 0                               |

Period of SYNC transmission in µs (0 = transmission disabled).

### 0x1007 - Synchronous window length
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | PERSIST_COMM   |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED32              | rw  | no  | no   | 0                               |

Synchronous window leghth in µs (0 = not used). All synchronous PDOs must be transmitted within this time window.

### 0x1008 - Manufacturer device name
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | ROM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| VISIBLE_STRING          | ro  | no  | no   | OreSat Linux Generic            |

### 0x1009 - Manufacturer hardware version
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | ROM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| VISIBLE_STRING          | ro  | no  | no   | 0.0                             |

### 0x100A - Manufacturer software version
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | ROM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| VISIBLE_STRING          | ro  | no  | no   | 0.0.0                           |

### 0x1010 - Store parameters
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| ARRAY       | STORAGE        | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x04          |
| 0x01 | Save all parameters   | UNSIGNED32 | rw  | no  | no   | 0x00000001    |
| 0x02 | Save communication parameters| UNSIGNED32 | rw  | no  | no   | 0x00000001    |
| 0x03 | Save application parameters| UNSIGNED32 | rw  | no  | no   | 0x00000001    |
| 0x04 | Save manufacturer defined parameters| UNSIGNED32 | rw  | no  | no   | 0x00000001    |

Sub-indexes 1 and above:
* Reading provides information about its storage functionality:
  * bit 1: If set, CANopen device saves parameters autonomously
  * bit 0: If set, CANopen device saves parameters on command
* Writing value 0x65766173 ('s','a','v','e' from LSB to MSB) stores corresponding data.

### 0x1011 - Restore default parameters
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| ARRAY       |                | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x04          |
| 0x01 | Restore all default parameters| UNSIGNED32 | rw  | no  | no   | 0x00000001    |
| 0x02 | Restore communication default parameters| UNSIGNED32 | rw  | no  | no   | 0x00000001    |
| 0x03 | Restore application default parameters| UNSIGNED32 | rw  | no  | no   | 0x00000001    |
| 0x04 | Restore manufacturer defined default parameters| UNSIGNED32 | rw  | no  | no   | 0x00000001    |

Sub-indexes 1 and above:
* Reading provides information about its restoring capability:
  * bit 0: If set, CANopen device restores parameters
* Writing value 0x64616F6C ('l','o','a','d' from LSB to MSB) restores corresponding data.

### 0x1014 - COB-ID EMCY
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         | EM_PROD        | PERSIST_COMM   |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED32              | rw  | no  | no   | 0x80+$NODEID                    |

* bit 31: If set, EMCY does NOT exist / is NOT valid
* bit 11-30: set to 0
* bit 0-10: 11-bit CAN-ID

### 0x1015 - Inhibit time EMCY
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | PERSIST_COMM   |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED16              | rw  | no  | no   | 0                               |

Inhibit time of emergency message in multiples of 100µs. The value 0 disables the inhibit time.

### 0x1016 - Consumer heartbeat time
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| ARRAY       | HB_CONS        | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x08          |
| 0x01 | Consumer heartbeat time| UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x02 | Consumer heartbeat time| UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x03 | Consumer heartbeat time| UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x04 | Consumer heartbeat time| UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x05 | Consumer heartbeat time| UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x06 | Consumer heartbeat time| UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x07 | Consumer heartbeat time| UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x08 | Consumer heartbeat time| UNSIGNED32 | rw  | no  | no   | 0x00000000    |

Consumer Heartbeat Time:
  * bit 24-31: set to 0
  * bit 16-23: Node ID of the monitored node. If 0 or greater than 127, sub-entry is not used.
  * bit 0-15: Heartbeat time in ms (if 0, sub-intry is not used). Value should be higher than the corresponding producer heartbeat time.

### 0x1017 - Producer heartbeat time
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         | HB_PROD        | PERSIST_COMM   |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED16              | rw  | no  | no   | 1000                            |

Heartbeat producer time in ms (0 = disable transmission).

### 0x1018 - Identity
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | ROM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x04          |
| 0x01 | Vendor-ID             | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x02 | Product code          | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x03 | Revision number       | UNSIGNED32 | ro  | no  | no   | 0x00000000    |
| 0x04 | Serial number         | UNSIGNED32 | ro  | no  | no   | 0x00000000    |

* Vendor-ID, assigned by CiA
* Product code, manufacturer specific
* Revision number:
  * bit 16-31: Major revision number (CANopen behavior has changed)
  * bit 0-15: Minor revision num. (CANopen behavior has not changed)
* Serial number, manufacturer specific

### 0x1019 - Synchronous counter overflow value
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | PERSIST_COMM   |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED8               | rw  | no  | no   | 0                               |

* Value 0: SYNC message is transmitted with data length 0.
* Value 1: reserved.
* Value 2-240: SYNC message has one data byte, which contains the counter.
* Value 241-255: reserved.

### 0x1023 - OS command
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x03          |
| 0x01 | Command               | DOMAIN     | rw  | no  | no   |               |
| 0x02 | Status                | UNSIGNED8  | ro  | no  | no   |               |
| 0x03 | Reply                 | DOMAIN     | ro  | no  | no   |               |

### 0x1029 - Error behavior
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| ARRAY       |                | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x02          |
| 0x01 | Communication error   | UNSIGNED8  | rw  | no  | no   | 0x00          |
| 0x02 | Profile- or manufacturer-specific error| UNSIGNED8  | rw  | no  | no   | 0x00          |

Sub-indexes 1 and above:
* Value 0x00: on error change to NMT state Pre-operational (only if currently in NMT state Operational)
* Value 0x01: on error do nothing
* Value 0x02: on error change to NMT state Stopped

### 0x1200 - SDO server parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      | SDO_SRV        | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x03          |
| 0x01 | COB-ID client to server| UNSIGNED32 | rw  | tr  | no   | 0x80000000    |
| 0x02 | COB-ID server to client| UNSIGNED32 | rw  | tr  | no   | 0x80000000    |
| 0x03 | Node-ID of the SDO client| UNSIGNED8  | rw  | no  | no   | 0x01          |

* Sub-indexes 1 and 2:
  * bit 31: If set, SDO does NOT exist / is NOT valid
  * bit 30: If set, value is assigned dynamically
  * bit 11-29: set to 0
  * bit 0-10: 11-bit CAN-ID
* Node-ID of the SDO client, 0x01 to 0x7F

### 0x1400 - RPDO communication parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      | RPDO           | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x05          |
| 0x01 | COB-ID used by RPDO   | UNSIGNED32 | rw  | no  | no   | 0x80000200+$NODEID|
| 0x02 | Transmission type     | UNSIGNED8  | rw  | no  | no   | 254           |
| 0x05 | Event timer           | UNSIGNED16 | rw  | no  | no   | 0             |

* COB-ID used by RPDO:
  * bit 31: If set, PDO does not exist / is not valid
  * bit 11-30: set to 0
  * bit 0-10: 11-bit CAN-ID
* Transmission type:
  * Value 0-240: synchronous, processed after next reception of SYNC object
  * Value 241-253: not used
  * Value 254: event-driven (manufacturer-specific)
  * Value 255: event-driven (device profile and application profile specific)
* Event timer in ms (0 = disabled) for deadline monitoring.

### 0x1401 - RPDO communication parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      | RPDO           | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x05          |
| 0x01 | COB-ID used by RPDO   | UNSIGNED32 | rw  | no  | no   | 0x80000300+$NODEID|
| 0x02 | Transmission type     | UNSIGNED8  | rw  | no  | no   | 254           |
| 0x05 | Event timer           | UNSIGNED16 | rw  | no  | no   | 0             |

* COB-ID used by RPDO:
  * bit 31: If set, PDO does not exist / is not valid
  * bit 11-30: set to 0
  * bit 0-10: 11-bit CAN-ID
* Transmission type:
  * Value 0-240: synchronous, processed after next reception of SYNC object
  * Value 241-253: not used
  * Value 254: event-driven (manufacturer-specific)
  * Value 255: event-driven (device profile and application profile specific)
* Event timer in ms (0 = disabled) for deadline monitoring.

### 0x1402 - RPDO communication parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      | RPDO           | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x05          |
| 0x01 | COB-ID used by RPDO   | UNSIGNED32 | rw  | no  | no   | 0x80000400+$NODEID|
| 0x02 | Transmission type     | UNSIGNED8  | rw  | no  | no   | 254           |
| 0x05 | Event timer           | UNSIGNED16 | rw  | no  | no   | 0             |

* COB-ID used by RPDO:
  * bit 31: If set, PDO does not exist / is not valid
  * bit 11-30: set to 0
  * bit 0-10: 11-bit CAN-ID
* Transmission type:
  * Value 0-240: synchronous, processed after next reception of SYNC object
  * Value 241-253: not used
  * Value 254: event-driven (manufacturer-specific)
  * Value 255: event-driven (device profile and application profile specific)
* Event timer in ms (0 = disabled) for deadline monitoring.

### 0x1403 - RPDO communication parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      | RPDO           | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x05          |
| 0x01 | COB-ID used by RPDO   | UNSIGNED32 | rw  | no  | no   | 0x80000500+$NODEID|
| 0x02 | Transmission type     | UNSIGNED8  | rw  | no  | no   | 254           |
| 0x05 | Event timer           | UNSIGNED16 | rw  | no  | no   | 0             |

* COB-ID used by RPDO:
  * bit 31: If set, PDO does not exist / is not valid
  * bit 11-30: set to 0
  * bit 0-10: 11-bit CAN-ID
* Transmission type:
  * Value 0-240: synchronous, processed after next reception of SYNC object
  * Value 241-253: not used
  * Value 254: event-driven (manufacturer-specific)
  * Value 255: event-driven (device profile and application profile specific)
* Event timer in ms (0 = disabled) for deadline monitoring.

### 0x1600 - RPDO mapping parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Number of mapped application objects in PDO| UNSIGNED8  | rw  | no  | no   | 0             |
| 0x01 | Mapping object 1      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x02 | Mapping object 2      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x03 | Mapping object 3      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x04 | Mapping object 4      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x05 | Mapping object 5      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x06 | Mapping object 6      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x07 | Mapping object 7      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x08 | Mapping object 8      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |

* Number of mapped application objects in PDO:
  * Value 0: mapping is disabled.
  * Value 1: sub-index 0x01 is valid.
  * Value 2-8: sub-indexes 0x01 to (0x02 to 0x08) are valid.
* Application object 1-8:
  * bit 16-31: index
  * bit 8-15: sub-index
  * bit 0-7: data length in bits

### 0x1601 - RPDO mapping parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Number of mapped application objects in PDO| UNSIGNED8  | rw  | no  | no   | 0             |
| 0x01 | Mapping object 1      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x02 | Mapping object 2      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x03 | Mapping object 3      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x04 | Mapping object 4      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x05 | Mapping object 5      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x06 | Mapping object 6      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x07 | Mapping object 7      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x08 | Mapping object 8      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |

* Number of mapped application objects in PDO:
  * Value 0: mapping is disabled.
  * Value 1: sub-index 0x01 is valid.
  * Value 2-8: sub-indexes 0x01 to (0x02 to 0x08) are valid.
* Application object 1-8:
  * bit 16-31: index
  * bit 8-15: sub-index
  * bit 0-7: data length in bits

### 0x1602 - RPDO mapping parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Number of mapped application objects in PDO| UNSIGNED8  | rw  | no  | no   | 0             |
| 0x01 | Mapping object 1      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x02 | Mapping object 2      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x03 | Mapping object 3      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x04 | Mapping object 4      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x05 | Mapping object 5      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x06 | Mapping object 6      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x07 | Mapping object 7      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x08 | Mapping object 8      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |

* Number of mapped application objects in PDO:
  * Value 0: mapping is disabled.
  * Value 1: sub-index 0x01 is valid.
  * Value 2-8: sub-indexes 0x01 to (0x02 to 0x08) are valid.
* Application object 1-8:
  * bit 16-31: index
  * bit 8-15: sub-index
  * bit 0-7: data length in bits

### 0x1603 - RPDO mapping parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Number of mapped application objects in PDO| UNSIGNED8  | rw  | no  | no   | 0             |
| 0x01 | Mapping object 1      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x02 | Mapping object 2      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x03 | Mapping object 3      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x04 | Mapping object 4      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x05 | Mapping object 5      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x06 | Mapping object 6      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x07 | Mapping object 7      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x08 | Mapping object 8      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |

* Number of mapped application objects in PDO:
  * Value 0: mapping is disabled.
  * Value 1: sub-index 0x01 is valid.
  * Value 2-8: sub-indexes 0x01 to (0x02 to 0x08) are valid.
* Application object 1-8:
  * bit 16-31: index
  * bit 8-15: sub-index
  * bit 0-7: data length in bits

### 0x1800 - TPDO communication parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      | TPDO           | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x06          |
| 0x01 | COB-ID used by TPDO   | UNSIGNED32 | rw  | no  | no   | 0xC0000180+$NODEID|
| 0x02 | Transmission type     | UNSIGNED8  | rw  | no  | no   | 254           |
| 0x03 | Inhibit time          | UNSIGNED16 | rw  | no  | no   | 0             |
| 0x04 | compatibility entry   | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x05 | Event timer           | UNSIGNED16 | rw  | no  | no   | 0             |
| 0x06 | SYNC start value      | UNSIGNED8  | rw  | no  | no   | 0             |

* COB-ID used by RPDO:
  * bit 31: If set, PDO does not exist / is not valid
  * bit 30: If set, NO RTR is allowed on this PDO
  * bit 11-29: set to 0
  * bit 0-10: 11-bit CAN-ID
* Transmission type:
  * Value 0: synchronous (acyclic)
  * Value 1-240: synchronous (cyclic every (1-240)-th sync)
  * Value 241-253: not used
  * Value 254: event-driven (manufacturer-specific)
  * Value 255: event-driven (device profile and application profile specific)
* Inhibit time in multiple of 100µs, if the transmission type is set to 254 or 255 (0 = disabled).
* Event timer interval in ms, if the transmission type is set to 254 or 255 (0 = disabled).
* SYNC start value
  * Value 0: Counter of the SYNC message shall not be processed.
  * Value 1-240: The SYNC message with the counter value equal to this value shall be regarded as the first received SYNC message.

### 0x1801 - TPDO communication parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      | TPDO           | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x06          |
| 0x01 | COB-ID used by TPDO   | UNSIGNED32 | rw  | no  | no   | 0xC0000280+$NODEID|
| 0x02 | Transmission type     | UNSIGNED8  | rw  | no  | no   | 254           |
| 0x03 | Inhibit time          | UNSIGNED16 | rw  | no  | no   | 0             |
| 0x04 | compatibility entry   | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x05 | Event timer           | UNSIGNED16 | rw  | no  | no   | 0             |
| 0x06 | SYNC start value      | UNSIGNED8  | rw  | no  | no   | 0             |

* COB-ID used by RPDO:
  * bit 31: If set, PDO does not exist / is not valid
  * bit 30: If set, NO RTR is allowed on this PDO
  * bit 11-29: set to 0
  * bit 0-10: 11-bit CAN-ID
* Transmission type:
  * Value 0: synchronous (acyclic)
  * Value 1-240: synchronous (cyclic every (1-240)-th sync)
  * Value 241-253: not used
  * Value 254: event-driven (manufacturer-specific)
  * Value 255: event-driven (device profile and application profile specific)
* Inhibit time in multiple of 100µs, if the transmission type is set to 254 or 255 (0 = disabled).
* Event timer interval in ms, if the transmission type is set to 254 or 255 (0 = disabled).
* SYNC start value
  * Value 0: Counter of the SYNC message shall not be processed.
  * Value 1-240: The SYNC message with the counter value equal to this value shall be regarded as the first received SYNC message.

### 0x1802 - TPDO communication parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      | TPDO           | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x06          |
| 0x01 | COB-ID used by TPDO   | UNSIGNED32 | rw  | no  | no   | 0xC0000380+$NODEID|
| 0x02 | Transmission type     | UNSIGNED8  | rw  | no  | no   | 254           |
| 0x03 | Inhibit time          | UNSIGNED16 | rw  | no  | no   | 0             |
| 0x04 | compatibility entry   | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x05 | Event timer           | UNSIGNED16 | rw  | no  | no   | 0             |
| 0x06 | SYNC start value      | UNSIGNED8  | rw  | no  | no   | 0             |

* COB-ID used by RPDO:
  * bit 31: If set, PDO does not exist / is not valid
  * bit 30: If set, NO RTR is allowed on this PDO
  * bit 11-29: set to 0
  * bit 0-10: 11-bit CAN-ID
* Transmission type:
  * Value 0: synchronous (acyclic)
  * Value 1-240: synchronous (cyclic every (1-240)-th sync)
  * Value 241-253: not used
  * Value 254: event-driven (manufacturer-specific)
  * Value 255: event-driven (device profile and application profile specific)
* Inhibit time in multiple of 100µs, if the transmission type is set to 254 or 255 (0 = disabled).
* Event timer interval in ms, if the transmission type is set to 254 or 255 (0 = disabled).
* SYNC start value
  * Value 0: Counter of the SYNC message shall not be processed.
  * Value 1-240: The SYNC message with the counter value equal to this value shall be regarded as the first received SYNC message.

### 0x1803 - TPDO communication parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      | TPDO           | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x06          |
| 0x01 | COB-ID used by TPDO   | UNSIGNED32 | rw  | no  | no   | 0xC0000480+$NODEID|
| 0x02 | Transmission type     | UNSIGNED8  | rw  | no  | no   | 254           |
| 0x03 | Inhibit time          | UNSIGNED16 | rw  | no  | no   | 0             |
| 0x04 | compatibility entry   | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x05 | Event timer           | UNSIGNED16 | rw  | no  | no   | 0             |
| 0x06 | SYNC start value      | UNSIGNED8  | rw  | no  | no   | 0             |

* COB-ID used by RPDO:
  * bit 31: If set, PDO does not exist / is not valid
  * bit 30: If set, NO RTR is allowed on this PDO
  * bit 11-29: set to 0
  * bit 0-10: 11-bit CAN-ID
* Transmission type:
  * Value 0: synchronous (acyclic)
  * Value 1-240: synchronous (cyclic every (1-240)-th sync)
  * Value 241-253: not used
  * Value 254: event-driven (manufacturer-specific)
  * Value 255: event-driven (device profile and application profile specific)
* Inhibit time in multiple of 100µs, if the transmission type is set to 254 or 255 (0 = disabled).
* Event timer interval in ms, if the transmission type is set to 254 or 255 (0 = disabled).
* SYNC start value
  * Value 0: Counter of the SYNC message shall not be processed.
  * Value 1-240: The SYNC message with the counter value equal to this value shall be regarded as the first received SYNC message.

### 0x1A00 - TPDO mapping parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Number of mapped application objects in PDO| UNSIGNED8  | rw  | no  | no   | 0             |
| 0x01 | Mapping object 1      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x02 | Mapping object 2      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x03 | Mapping object 3      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x04 | Mapping object 4      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x05 | Mapping object 5      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x06 | Mapping object 6      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x07 | Mapping object 7      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x08 | Mapping object 8      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |

* Number of mapped application objects in PDO:
  * Value 0: mapping is disabled.
  * Value 1: sub-index 0x01 is valid.
  * Value 2-8: sub-indexes 0x01 to (0x02 to 0x08) are valid.
* Application object 1-8:
  * bit 16-31: index
  * bit 8-15: sub-index
  * bit 0-7: data length in bits

### 0x1A01 - TPDO mapping parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Number of mapped application objects in PDO| UNSIGNED8  | rw  | no  | no   | 0             |
| 0x01 | Mapping object 1      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x02 | Mapping object 2      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x03 | Mapping object 3      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x04 | Mapping object 4      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x05 | Mapping object 5      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x06 | Mapping object 6      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x07 | Mapping object 7      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x08 | Mapping object 8      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |

* Number of mapped application objects in PDO:
  * Value 0: mapping is disabled.
  * Value 1: sub-index 0x01 is valid.
  * Value 2-8: sub-indexes 0x01 to (0x02 to 0x08) are valid.
* Application object 1-8:
  * bit 16-31: index
  * bit 8-15: sub-index
  * bit 0-7: data length in bits

### 0x1A02 - TPDO mapping parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Number of mapped application objects in PDO| UNSIGNED8  | rw  | no  | no   | 0             |
| 0x01 | Mapping object 1      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x02 | Mapping object 2      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x03 | Mapping object 3      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x04 | Mapping object 4      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x05 | Mapping object 5      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x06 | Mapping object 6      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x07 | Mapping object 7      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x08 | Mapping object 8      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |

* Number of mapped application objects in PDO:
  * Value 0: mapping is disabled.
  * Value 1: sub-index 0x01 is valid.
  * Value 2-8: sub-indexes 0x01 to (0x02 to 0x08) are valid.
* Application object 1-8:
  * bit 16-31: index
  * bit 8-15: sub-index
  * bit 0-7: data length in bits

### 0x1A03 - TPDO mapping parameter
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | PERSIST_COMM   |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Number of mapped application objects in PDO| UNSIGNED8  | rw  | no  | no   | 0             |
| 0x01 | Mapping object 1      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x02 | Mapping object 2      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x03 | Mapping object 3      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x04 | Mapping object 4      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x05 | Mapping object 5      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x06 | Mapping object 6      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x07 | Mapping object 7      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |
| 0x08 | Mapping object 8      | UNSIGNED32 | rw  | no  | no   | 0x00000000    |

* Number of mapped application objects in PDO:
  * Value 0: mapping is disabled.
  * Value 1: sub-index 0x01 is valid.
  * Value 2-8: sub-indexes 0x01 to (0x02 to 0x08) are valid.
* Application object 1-8:
  * bit 16-31: index
  * bit 8-15: sub-index
  * bit 0-7: data length in bits

### 0x1F80 - NMTStartup
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | PERSIST_COMM   |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED32              | rw  | no  | no   | 0x00000008                      |

This object configures the start-up behavior of a device that is able to perform the NMT.

Manufacturer Specific Parameters {#manufacturer-specific-parameters}
--------------------------------------------------------------------

### 0x2000 - BUS management
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | PERSIST_MFR    |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x04          |
| 0x01 | Bdefault              | UNSIGNED8  | rw  | no  | no   | 0             |
| 0x02 | Ttoggle               | UNSIGNED8  | rw  | no  | no   | 0             |
| 0x03 | Ntoggle               | UNSIGNED8  | rw  | no  | no   | 0             |
| 0x04 | Ctoggle               | UNSIGNED8  | rw  | no  | no   | 0             |

CAN Bus redundancy management as defined in ECSS-E-ST-50-15C
Bdefault specifies the bus to be considered active after a node power-on, node hardware reset.
Ttoggle specifies the number of Consumer Heartbeat times during which the node is required to be listeningfor an NMT HB message on a particular bus before switching to the other bus.
Ntoggle specifies the number of toggles between the Nominal and Redundant bus in case of no HB message being detected. If an even number is used the last toggle puts the system into Bdefault.
The counter of Ntoggles (bus toggles) shows the count of the number of toggles that have already been performed by the device.

### 0x2010 - SCET
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | RAM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED64              | rw  | tr  | no   | 0                               |

CCSDS Unsegmented Time Code (CUC) object for Spacecraft Elapsed Time (SCET) get/set methods

### 0x2011 - UTC
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | RAM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED64              | rw  | tr  | no   | 0                               |

CCSDS Day Segmented Time Code (CDS) object for UTC time get/set methods

### 0x2100 - Error status bits
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | RAM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| OCTET_STRING            | ro  | no  | no   | 00 00 00 00 00 00 00 00 00 00   |

Error Status Bits indicates error conditions inside stack or inside application. Specific bit is set by CO_errorReport() function, when error occurs in program. It can be reset by CO_errorReset() function, if error is solved. Emergency message is sent on each change of any Error Status Bit. If critical bits are set, node will not be able to stay in operational state. For more information see file CO_Emergency.h.

Default error status bits are:

Communication or protocol errors from driver (informative):
00 - ERROR_NO_ERROR - Error Reset or No Error.
01 - ERROR_CAN_BUS_WARNING - CAN bus warning.
02 - ERROR_RXMSG_WRONG_LENGTH - Wrong data length of received CAN message.
03 - ERROR_RXMSG_OVERFLOW - Previous received CAN message wasn't processed yet.
04 - ERROR_RPDO_WRONG_LENGTH - Wrong data length of received PDO.
05 - ERROR_RPDO_OVERFLOW - Previous received PDO wasn't processed yet.
06 - ERROR_CAN_RX_BUS_PASSIVE - CAN receive bus is passive.
07 - ERROR_CAN_TX_BUS_PASSIVE - CAN transmit bus is passive.

Communication or protocol errors from driver (critical):
08 - ERROR_08_reserved - (reserved)
09 - ERROR_09_reserved - (reserved)
0A - ERROR_CAN_TX_BUS_OFF - CAN transmit bus is off.
0B - ERROR_CAN_RXB_OVERFLOW - CAN module receive buffer has overflowed.
0C - ERROR_CAN_TX_OVERFLOW - CAN transmit buffer has overflowed.
0D - ERROR_TPDO_OUTSIDE_WINDOW - TPDO is outside SYNC window.
0E - ERROR_CAN_CONFIGURATION_FAILED - Configuration of CAN module CAN failed (Rx or Tx).
0F - ERROR_0F_reserved - (reserved)

Communication or protocol errors (informative):
10 - ERROR_NMT_WRONG_COMMAND - Wrong NMT command received.
11 - ERROR_SYNC_EARLY - SYNC message was too early.
12 - ERROR_12_reserved - (reserved)
13 - ERROR_13_reserved - (reserved)
14 - ERROR_14_reserved - (reserved)
15 - ERROR_15_reserved - (reserved)
16 - ERROR_16_reserved - (reserved)
17 - ERROR_17_reserved - (reserved)

Communication or protocol errors (critical):
18 - ERROR_SYNC_TIME_OUT - SYNC message timeout.
19 - ERROR_SYNC_LENGTH - Unexpected SYNC data length
1A - ERROR_PDO_WRONG_MAPPING - Error with PDO mapping.
1B - ERROR_HEARTBEAT_CONSUMER - Heartbeat consumer timeout.
1C - ERROR_HEARTBEAT_CONSUMER_REMOTE_RESET - Heartbeat consumer detected remote node reset.
1D - ERROR_1D_reserved - (reserved)
1E - ERROR_1E_reserved - (reserved)
1F - ERROR_1F_reserved - (reserved)

Generic errors (informative):
20 - ERROR_20_reserved - (reserved)
21 - ERROR_21_reserved - (reserved)
22 - ERROR_22_reserved - (reserved)
23 - ERROR_23_reserved - (reserved)
24 - ERROR_24_reserved - (reserved)
25 - ERROR_25_reserved - (reserved)
26 - ERROR_26_reserved - (reserved)
27 - ERROR_27_reserved - (reserved)

Generic errors (critical):
28 - ERROR_WRONG_ERROR_REPORT - Wrong parameters to <CO_errorReport()> function.
29 - ERROR_ISR_TIMER_OVERFLOW - Timer task has overflowed.
2A - ERROR_MEMORY_ALLOCATION_ERROR - Unable to allocate memory for objects.
2B - ERROR_GENERIC_ERROR - Generic error, test usage.
2C - ERROR_MAIN_TIMER_OVERFLOW - Mainline function exceeded maximum execution time.
2D - ERROR_INTERNAL_STATE_APPL - Error in application software internal state.
2E - ERROR_2E_reserved - (reserved)
2F - ERROR_2F_reserved - (reserved)

Manufacturer specific errors:
Manufacturer may define its own constants up to index 0xFF. Of course, he must then define large enough buffer for error status bits (up to 32 bytes).

### 0x2101 - CAN node ID
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | RAM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED8               | rw  | no  | no   | 0x10                            |

### 0x3001 - Board info
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x1C          |
| 0x01 | OS name               | DOMAIN     | ro  | no  | no   |               |
| 0x02 | OS distro             | DOMAIN     | ro  | no  | no   |               |
| 0x03 | OS kernel version     | DOMAIN     | ro  | no  | no   |               |
| 0x04 | hostname              | DOMAIN     | ro  | no  | no   |               |
| 0x05 | Uptime                | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x06 | Number of CPUs        | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x07 | CPU architecture      | DOMAIN     | ro  | no  | no   |               |
| 0x08 | CPU governor          | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x09 | CPU frequency         | UNSIGNED16 | ro  | no  | no   | 0             |
| 0x0A | Number of remoteprocs | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x0B | RemoteprocX selector  | UNSIGNED8  | rw  | no  | no   | 0             |
| 0x0C | RemoteprocX name      | DOMAIN     | ro  | no  | no   |               |
| 0x0D | RemoteprocX state     | DOMAIN     | ro  | no  | no   |               |
| 0x0E | Load average 1min     | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x0F | Load average 5min     | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x10 | Load average 15min    | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x11 | Ram total             | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x12 | Ram free              | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x13 | Ram shared            | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x14 | Ram buffered          | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x15 | Ram percent           | UNSIGNED8  | ro  | t   | no   | 0             |
| 0x16 | Swap total            | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x17 | Swap free             | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x18 | Swap percent          | UNSIGNED8  | ro  | t   | no   | 0             |
| 0x19 | Procs                 | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x1A | Root parition total   | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x1B | Root parition free    | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x1C | Root parition percent | UNSIGNED8  | ro  | t   | no   | 0             |

### 0x3002 - File caches
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x09          |
| 0x01 | Fread cache len       | UNSIGNED8  | ro  | t   | no   | 0             |
| 0x02 | Fwrite cache len      | UNSIGNED8  | ro  | t   | no   | 0             |
| 0x03 | Cache selector        | UNSIGNED8  | rw  | no  | no   | 0             |
| 0x04 | Filter                | DOMAIN     | rw  | no  | no   |               |
| 0x05 | Cache len             | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x06 | Iterator              | UNSIGNED32 | rw  | no  | no   | 0             |
| 0x07 | File name             | DOMAIN     | ro  | no  | no   |               |
| 0x08 | File size             | UNSIGNED32 | ro  | no  | no   | 0             |
| 0x09 | Delete file           | DOMAIN     | wo  | no  | no   |               |

### 0x3003 - Fread
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x04          |
| 0x01 | File name             | DOMAIN     | rw  | no  | no   |               |
| 0x02 | File data             | DOMAIN     | ro  | no  | no   |               |
| 0x03 | Reset                 | DOMAIN     | wo  | no  | no   |               |
| 0x04 | Delete file           | DOMAIN     | wo  | no  | no   |               |

### 0x3004 - Fwrite
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x03          |
| 0x01 | File name             | DOMAIN     | rw  | no  | no   |               |
| 0x02 | File data             | DOMAIN     | wo  | no  | no   |               |
| 0x03 | Reset                 | DOMAIN     | wo  | no  | no   |               |

### 0x3005 - App manager
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x04          |
| 0x01 | Total apps            | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x02 | Select app            | UNSIGNED8  | rw  | no  | no   | 0             |
| 0x03 | App name              | DOMAIN     | ro  | no  | no   |               |
| 0x04 | Daemon state          | INTEGER8   | rw  | no  | no   | 0             |

### 0x3006 - Get log
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| VAR         |                | RAM            |

| Data Type               | SDO | PDO | SRDO | Default Value                   |
| ----------------------- | --- | --- | ---- | ------------------------------- |
| UNSIGNED8               | ro  | no  | no   | 0                               |

### 0x3100 - Updater
| Object Type | Count Label    | Storage Group  |
| ----------- | -------------- | -------------- |
| RECORD      |                | RAM            |

| Sub  | Name                  | Data Type  | SDO | PDO | SRDO | Default Value |
| ---- | --------------------- | ---------- | --- | --- | ---- | ------------- |
| 0x00 | Highest sub-index supported| UNSIGNED8  | ro  | no  | no   | 0x05          |
| 0x01 | Status                | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x02 | Updates available     | UNSIGNED8  | ro  | no  | no   | 0             |
| 0x03 | List updates          | DOMAIN     | ro  | no  | no   |               |
| 0x04 | Update                | UNSIGNED8  | wo  | no  | no   |               |
| 0x05 | Make status file      | UNSIGNED8  | wo  | no  | no   |               |

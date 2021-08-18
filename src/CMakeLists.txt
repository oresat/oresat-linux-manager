# src

set(CANOPEN_DIR CANopenNode)

set(CANOPENNODE_SOURCES
    ${CANOPEN_DIR}/301/CO_NMT_Heartbeat.c
    ${CANOPEN_DIR}/301/CO_HBconsumer.c
    ${CANOPEN_DIR}/301/CO_Emergency.c
    ${CANOPEN_DIR}/301/CO_SDOclient.c
    ${CANOPEN_DIR}/301/CO_SDOserver.c
    ${CANOPEN_DIR}/301/CO_SYNC.c
    ${CANOPEN_DIR}/301/CO_PDO.c
    ${CANOPEN_DIR}/301/crc16-ccitt.c
    ${CANOPEN_DIR}/301/CO_fifo.c
    ${CANOPEN_DIR}/CANopen.c
    )


set(CANOPENNODE_HEADERS
    CO_driver_custom.h
    ${CANOPEN_DIR}/301/CO_config.h
    ${CANOPEN_DIR}/301/CO_driver.h
    ${CANOPEN_DIR}/301/CO_HBconsumer.h
    ${CANOPEN_DIR}/301/CO_NMT_Heartbeat.h
    ${CANOPEN_DIR}/301/CO_Emergency.h
    ${CANOPEN_DIR}/301/CO_SDOclient.h
    ${CANOPEN_DIR}/301/CO_SDOserver.h
    ${CANOPEN_DIR}/301/CO_SYNC.h
    ${CANOPEN_DIR}/301/CO_PDO.h
    ${CANOPEN_DIR}/301/crc16-ccitt.h
    ${CANOPEN_DIR}/301/CO_fifo.h
    ${CANOPEN_DIR}/CANopen.h
    )

add_library(CANopenNode ${CANOPENNODE_SOURCES} ${CANOPENNODE_HEADERS})

target_link_libraries(CANopenNode
    socketCAN
    object_dictionary
    )

target_include_directories(CANopenNode PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/${CANOPEN_DIR}
    )

add_subdirectory(socketCAN_mod)
add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(manitory_apps)
add_subdirectory(daemons)
add_subdirectory(boards)

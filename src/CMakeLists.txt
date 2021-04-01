# src

set(CANOPEN_DIR CANopenNode)
set(STACK_DRIVER_DIR ${CANOPEN_DIR}/socketCAN)

set(CANOPENNODE_SOURCES
    ${STACK_DRIVER_DIR}/CO_driver.c
    ${STACK_DRIVER_DIR}/CO_error.c
    ${STACK_DRIVER_DIR}/CO_epoll_interface.c
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
    ${STACK_DRIVER_DIR}/CO_driver_target.h
    ${STACK_DRIVER_DIR}/CO_error.h
    ${STACK_DRIVER_DIR}/CO_epoll_interface.h
    ${STACK_DRIVER_DIR}/CO_error_msgs.h
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

target_include_directories(CANopenNode PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${CANOPEN_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${STACK_DRIVER_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD_DIR}/object_dictionary
    )

add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(daemon_modules)
add_subdirectory(boards)

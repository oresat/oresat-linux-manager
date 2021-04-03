# socketCAN_mod

set(SOCKETCAN_SOURCES
    CO_driver.c
    CO_epoll_interface.c
    CO_error.c
    )

set(SOCKETCAN_HEADERS
    CO_driver_target.h
    CO_epoll_interface.h
    CO_error.h
    CO_error_msgs.h
    )

add_library(socketCAN ${SOCKETCAN_SOURCES} ${SOCKETCAN_HEADERS})

target_link_libraries(socketCAN
    CANopenNode
    common
    )

target_include_directories(socketCAN PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

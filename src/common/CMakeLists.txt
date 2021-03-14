
set(COMMON_SOURCES
    log_message.c
    )

set(COMMON_HEADERS
    log_message.h
    utility.h
    )

add_library(common ${COMMON_SOURCES} ${COMMON_HEADERS})

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

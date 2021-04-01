# common

set(COMMON_SOURCES
    log_message.c
    olm_file.c
    olm_file_cache.c
    utility.c
    )

set(COMMON_HEADERS
    log_message.h
    olm_app.h
    olm_file.h
    olm_file_cache.h
    utility.h
    )

add_library(common ${COMMON_SOURCES} ${COMMON_HEADERS})

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

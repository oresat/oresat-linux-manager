# common

set(COMMON_SOURCES
    ecss_time.c
    logging.c
    olm_file.c
    olm_file_cache.c
    utility.c
    )


set(COMMON_HEADERS
    ecss_time.h
    logging.h
    olm_app.h
    olm_file.h
    olm_file_cache.h
    utility.h
    )

add_library(common ${COMMON_SOURCES} ${COMMON_HEADERS})

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

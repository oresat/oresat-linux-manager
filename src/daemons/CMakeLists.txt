# daemons

set(DAEMONS_SOURCES
    gps.c
    logind.c
    star_tracker.c
    systemd.c
    updaterd.c
    )

set(DAEMONS_HEADERS
    gps.h
    logind.h
    star_tracker.h
    systemd.h
    updaterd.h
    )

add_library(daemons ${DAEMONS_SOURCES} ${DAEMONS_HEADERS})

target_link_libraries(daemons common core)

target_include_directories(daemons PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

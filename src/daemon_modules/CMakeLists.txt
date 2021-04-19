# daemon_modules

set(DAEMON_MODULES_SOURCES
    gps.c
    logind.c
    star_tracker.c
    systemd.c
    updaterd.c
    )

set(DAEMON_MODULES_HEADERS
    gps.h
    logind.h
    star_tracker.h
    systemd.h
    updaterd.h
    )

add_library(daemon_modules ${DAEMON_MODULES_SOURCES} ${DAEMON_MODULES_HEADERS})

target_link_libraries(daemon_modules common core)

target_include_directories(daemon_modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

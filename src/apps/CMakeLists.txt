# apps

set(APPS_SOURCES
    linux_updater_app.c
    logind_app.c
    star_tracker_app.c
    systemd_app.c
    template_app.c
    )

set(APPS_HEADERS
    linux_updater_app.h
    logind_app.h
    star_tracker_app.h
    systemd_app.h
    template_app.h
    )

add_library(apps ${APPS_SOURCES} ${APPS_HEADERS})

target_link_libraries(apps common core)

target_include_directories(apps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

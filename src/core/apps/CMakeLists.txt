# core apps

set(CORE_APPS_SOURCES
    logind_app.c
    systemd_app.c
    linux_updater_app.c
    )

set(CORE_APPS_HEADERS
    logind_app.h
    systemd_app.h
    linux_updater_app.h
    )

add_library(core_apps ${CORE_APPS_SOURCES} ${CORE_APPS_HEADERS})

target_link_libraries(core_apps common core)

target_include_directories(core_apps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

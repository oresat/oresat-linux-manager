
set(SYSTEM_APPS_SOURCES
    system_apps.c
    linux_updater_app.c
    )

set(SYSTEM_APPS_HEADERS
    linux_updater_app.h
    )

add_library(system_apps ${SYSTEM_APPS_SOURCES} ${SYSTEM_APPS_HEADERS})

target_link_libraries(system_apps olm_common)

target_include_directories(system_apps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# core

set(CORE_SOURCES
    cpufreq.c
    dbus_controller.c
    )

set(CORE_HEADERS
    cpufreq.h
    dbus_controller.h
    olm_app.h
    board_main.h
    )

add_library(core ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(core common board)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(apps)
add_subdirectory(ODFs)

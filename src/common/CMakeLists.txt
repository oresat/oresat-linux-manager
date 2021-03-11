
set(OLM_COMMON_SOURCES
    board_info.c
    CO_fread.c
    CO_fwrite.c
    cpufreq.c
    daemon_manager.c
    dbus_controller.c
    logind_interface.c
    log_message.c
    OD_helpers.c
    )

set(OLM_COMMON_HEADERS
    app_include.h
    apps.h
    board_info.h
    CO_fread.h
    CO_fwrite.h
    cpufreq.h
    daemon_manager.h
    dbus_controller.h
    logind_interface.h
    log_message.h
    OD_helpers.h
    )

add_library(olm_common ${OLM_COMMON_SOURCES} ${OLM_COMMON_HEADERS})

target_link_libraries(olm_common board_apps)
target_link_libraries(olm_common CANopenNode)

target_include_directories(olm_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

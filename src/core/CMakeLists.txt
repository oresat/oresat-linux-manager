# core

set(CORE_SOURCES
    app_manager.c
    CO_fstream_odf.c
    configs.c
    cpufreq.c
    file_caches_odf.c
    olm_control_odf.c
    os_command.c
    system_info.c
    time_sync.c
    time_producer.c
    )

set(CORE_HEADERS
    app_manager.h
    board_main.h
    CO_fstream_odf.h
    configs.h
    cpufreq.h
    file_caches_odf.h
    olm_control_odf.h
    os_command.h
    system_info.h
    time_sync.h
    time_producer.h
    )

add_library(core ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(core
    CANopenNode
    common
    board
    object_dictionary
    )

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

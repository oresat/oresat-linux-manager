# core

set(CORE_SOURCES
    app_manager_odf.c
    async_loop.c
    board_info.c
    CO_fstream_odf.c
    cpufreq.c
    file_caches_odf.c
    linux_updater_odf.c
    logind_odf.c
    )

set(CORE_HEADERS
    app_manager_odf.h
    async_loop.h
    board_info.h
    board_main.h
    CO_fstream_odf.h
    cpufreq.h
    file_caches_odf.h
    globals.h
    linux_updater_odf.h
    logind_odf.h
    )

add_library(core ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(core common board)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

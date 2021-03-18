# core

set(CORE_SOURCES
    cpufreq.c
    app_manager.c
    olm_file.c
    olm_file_cache.c
    )

set(CORE_HEADERS
    cpufreq.h
    app_manager.h
    olm_app.h
    olm_file.h
    olm_file_cache.c
    board_main.h
    )

add_library(core ${CORE_SOURCES} ${CORE_HEADERS})

target_link_libraries(core common board)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(apps)
add_subdirectory(ODFs)

# core ODFs

set(CORE_ODF_SOURCES
    board_info.c
    CO_fread.c
    CO_fwrite.c
    daemon_manager.c
    logind_odf.c
    linux_updater_odf.c
    )

set(CORE_ODF_HEADERS
    board_info.h
    CO_fread.h
    CO_fwrite.h
    daemon_manager.h
    logind_odf.h
    linux_updater_odf.h
    )

add_library(core_ODFs ${CORE_ODF_SOURCES} ${CORE_ODF_HEADERS})

target_link_libraries(core_ODFs
    CANopenNode
    object_dictionary
    common
    core
    core_apps
    )

target_include_directories(core_ODFs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

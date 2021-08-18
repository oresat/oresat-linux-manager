# manitory_apps

set(MANITORY_APPS_SOURCES
    updater_app.c
    )

set(MANITORY_APPS_HEADERS
    updater_app.h
    )

add_library(manitory_apps ${MANITORY_APPS_SOURCES} ${MANITORY_APPS_HEADERS})

target_link_libraries(manitory_apps
    CANopenNode
    common
    object_dictionary
    daemons
    )

target_include_directories(manitory_apps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# apps

set(APPS_SOURCES
    template_app.c
    star_tracker_app.c
    )

set(APPS_HEADERS
    template_app.h
    star_tracker_app.h
    )

add_library(apps ${APPS_SOURCES} ${APPS_HEADERS})

target_link_libraries(apps common core)

target_include_directories(apps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


set(OD_SOURCES CO_OD.c)
set(OD_HEADERS CO_OD.h)
add_library(object_dictionary ${OD_SOURCES} ${OD_HEADERS})

target_link_libraries(object_dictionary CANopenNode)

target_include_directories(object_dictionary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Star Tracker board

set(BOARD_SOURCES
    board_main.c
    star_tracker_app.c
    )

set(BOARD_HEADERS
    star_tracker_app.h
    )

add_library(board ${BOARD_SOURCES} ${BOARD_HEADERS})

target_link_libraries(board
    CANopenNode
    core
    common
    manitory_apps
    daemon_modules
    )

target_include_directories(board PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(object_dictionary)

##############################################################################
# CPack info

# NOTE: general CPACK info is in ../CMakeLists.txt

set(CPACK_DEBIAN_PACKAGE_NAME "olm-star-tracker")
set(CPACK_DEBIAN_PACKAGE_VERSION "1.0.0-0")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "CANopen frontend to the Oresat Star Tracker board")
set(CPACK_DEBIAN_PACKAGE_CONFLICTS "olm-generic olm-cfc olm-gps olm-dxwifi")

# If this version of OLM need extra packages add_dependencies do:
# set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS} extra-package)"

# must be set/included after the rest, shouldn't need to be updated
set(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}_${CPACK_DEBIAN_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
include(CPack)

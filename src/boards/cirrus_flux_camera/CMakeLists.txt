# CFC board

set(BOARD_APPS_SOURCES
    board_apps.c
    pru_camera_test_app.c
    )

set(BOARD_APPS_HEADERS
    pru_camera_test_app.h
    )

add_library(board_apps ${BOARD_APPS_SOURCES} ${BOARD_APPS_HEADERS})

target_link_libraries(board_apps CANopenNode)
target_link_libraries(board_apps olm_common)

target_include_directories(board_apps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(object_dictionary)

##############################################################################
# CPack info

# NOTE: general CPACK info is in ../CMakeLists.txt

set(CPACK_DEBIAN_PACKAGE_NAME "olm-cfc")
set(CPACK_DEBIAN_PACKAGE_VERSION "0.1.1-0")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "CANopen frontend to the Oresat CFC board")
set(CPACK_DEBIAN_PACKAGE_CONFLICTS "olm-generic olm-gps olm-live olm-star-tracker")

# If this version of OLM need extra packages add_dependencies do:
# set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS} extra-package"

# must be set/included after the rest, shouldn't need to be updated
set(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}_${CPACK_DEBIAN_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
include(CPack)

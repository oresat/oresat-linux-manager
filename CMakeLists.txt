if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build, it is bad practice.\nTry 'cd build && cmake ..' instead.")
endif()

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(OreSat-Linux-Manager C)


##############################################################################
# Figure out which board

if(NOT BOARD)
    message(FATAL_ERROR "No board specified\n  ie: cmake -DBOARD=star-tracker ..")
endif()

# ignore case
STRING(TOLOWER "${BOARD}" BOARD)

if(BOARD MATCHES "cirrus-flux-camera" OR BOARD MATCHES "cirrus_flux_camera" OR BOARD MATCHES "cfc")
    set(BOARD cirrus_flux_camera)
    set(PACKAGE_NAME "olm-cfc")
    set(OLM_VERSION 0.1.0-0)
    set(CPACK_DEBIAN_PACKAGE_CONFLICTS "olm-gps olm-live olm-startracker olm-template")
elseif(BOARD MATCHES "gps")
    set(PACKAGE_NAME "olm-gps")
    set(OLM_VERSION 0.1.0-0)
    set(CPACK_DEBIAN_PACKAGE_CONFLICTS "olm-cfc olm-live olm-startracker olm-template")
elseif(BOARD MATCHES "live")
    set(PACKAGE_NAME "olm-live")
    set(OLM_VERSION 0.1.0-0)
    set(CPACK_DEBIAN_PACKAGE_CONFLICTS "olm-cfc olm-gps olm-startracker olm-template")
elseif(BOARD MATCHES "star-tracker" OR BOARD MATCHES "star_tracker" OR BOARD MATCHES "st" OR BOARD MATCHES "startracker")
    set(BOARD star_tracker)
    set(PACKAGE_NAME "olm-startracker")
    set(OLM_VERSION 0.1.0-0)
    set(CPACK_DEBIAN_PACKAGE_CONFLICTS "olm-cfc olm-gps olm-live olm-template")
elseif(BOARD MATCHES "template")
    set(PACKAGE_NAME "olm-template")
    set(OLM_VERSION 0.1.0-0)
    set(CPACK_DEBIAN_PACKAGE_CONFLICTS "olm-cfc olm-gps olm-live olm-startracker")
else()
    message(FATAL_ERROR "${BOARD} is not a valid board")
endif()

message(STATUS "${BOARD} Board selected")


##############################################################################
# Check Linux distribution / verion / kernel version

set(LINUX_DISTRIBUTION "")

if(EXISTS "/etc/os-release")
    execute_process(COMMAND cat /etc/os-release
        COMMAND grep -m1 NAME
        COMMAND awk -F= "{ print $2 }"
        COMMAND tr "\n" " "
        COMMAND sed "s/ //"
        OUTPUT_VARIABLE LINUX_DISTRIBUTION
        RESULT_VARIABLE LINUX_ID_RESULT
    )
    if(${LINUX_DISTRIBUTION} MATCHES "Debian")
        set(LINUX_DISTRIBUTION "Debian")
    endif()
else()
    message(FATAL_ERROR "Missing /etc/os-release. Not a Linux based system?")
endif()


##############################################################################
# Deal with dependencies

# pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# pkg-config
find_package(PkgConfig REQUIRED)

# libsystemd
pkg_check_modules(LIBSYSTEMD REQUIRED libsystemd)

# doxygen
find_package(Doxygen REQUIRED)


##############################################################################
# Deal with git submodule

find_package(Git)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "git check failed")
endif()
if(NOT EXISTS "../src/CANopenNode/.git")
    message(STATUS "Running: git submoduke update --init")
    execute_process(COMMAND git submodule update --init WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()


##############################################################################
# Release vs debug modes (set CFLAGS, LDFLAGS, etc)
# to use: cmake -DCMAKE_BUILD_TYPE=Debug .

# default to release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")


##############################################################################
# Check if make or ninja

if(CMAKE_MAKE_PROGRAM MATCHES "make")
    set(CMAKE_MAKE_PROGRAM_PRETTY_NAME "make")
endif()
if(CMAKE_MAKE_PROGRAM MATCHES "ninja")
    set(CMAKE_MAKE_PROGRAM_PRETTY_NAME "ninja")
endif()
if(NOT CMAKE_MAKE_PROGRAM_PRETTY_NAME)
    set(CMAKE_MAKE_PROGRAM_PRETTY_NAME "${CMAKE_MAKE_PROGRAM}")
endif()


##############################################################################
# Doygen

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)


##############################################################################
# Get source files

# all paths to source directories
set(STACK_DRIVER_DIR src/socketCAN)
set(CANOPEN_DIR src/CANopenNode)
set(OD_DIR src/boards/${BOARD}/object_dictionary)
set(COMMON_DIR src/common)
set(SYSTEM_APPS_DIR src/system_apps)
set(BOARD_APPS_DIR src/boards/${BOARD})

set(OLM_INCLUDE_DIRS
    ${CANOPEN_DIR}/301
    ${STACK_DRIVER_DIR}
    ${CANOPEN_DIR}
    ${OD_DIR}
    ${COMMON_DIR}
    ${SYSTEM_APPS_DIR}
    ${BOARD_APPS_DIR}
)

# deal with each board having different apps
# NOTE every time an app is add "cmake .." need to be call manually
aux_source_directory(${BOARD_APPS_DIR} BOARD_APPS_SOURCES)
aux_source_directory(${SYSTEM_APPS_DIR} SYSTEM_APPS_SOURCES)

set(CANOPENNODE_SOURCES
    ${STACK_DRIVER_DIR}/CO_driver.c
    ${STACK_DRIVER_DIR}/CO_error.c
    ${STACK_DRIVER_DIR}/CO_Linux_threads.c
    ${CANOPEN_DIR}/301/CO_Emergency.c
    ${CANOPEN_DIR}/301/CO_fifo.c
    ${CANOPEN_DIR}/301/CO_HBconsumer.c
    ${CANOPEN_DIR}/301/CO_NMT_Heartbeat.c
    ${CANOPEN_DIR}/301/CO_PDO.c
    ${CANOPEN_DIR}/301/CO_SDOclient.c
    ${CANOPEN_DIR}/301/CO_SDOserver.c
    ${CANOPEN_DIR}/301/CO_SYNC.c
    ${CANOPEN_DIR}/301/CO_TIME.c
    ${CANOPEN_DIR}/301/crc16-ccitt.c
    ${CANOPEN_DIR}/309/CO_gateway_ascii.c
    ${CANOPEN_DIR}/CANopen.c
)

set(CANOPENNODE_HEADERS
    ${STACK_DRIVER_DIR}/CO_error.h
    ${STACK_DRIVER_DIR}/CO_Linux_threads.h
    ${CANOPEN_DIR}/301/CO_config.h
    ${CANOPEN_DIR}/301/CO_driver.h
    ${CANOPEN_DIR}/301/CO_Emergency.h
    ${CANOPEN_DIR}/301/CO_fifo.h
    ${CANOPEN_DIR}/301/CO_HBconsumer.h
    ${CANOPEN_DIR}/301/CO_NMT_Heartbeat.h
    ${CANOPEN_DIR}/301/CO_PDO.h
    ${CANOPEN_DIR}/301/CO_SDOclient.h
    ${CANOPEN_DIR}/301/CO_SDOserver.h
    ${CANOPEN_DIR}/301/CO_SYNC.h
    ${CANOPEN_DIR}/301/CO_TIME.h
    ${CANOPEN_DIR}/301/crc16-ccitt.h
    ${CANOPEN_DIR}/309/CO_gateway_ascii.h
    ${CANOPEN_DIR}/CANopen.h
)


add_library(CANopenNode ${CANOPENNODE_SOURCES} ${CANOPENNODE_HEADERS})
target_include_directories(CANopenNode PUBLIC ${OLM_INCLUDE_DIRS})

set(SOURCE_FILES
    ${OD_DIR}/CO_OD.c
    ${COMMON_DIR}/log_message.c
    ${COMMON_DIR}/CO_fread.c
    ${COMMON_DIR}/CO_fwrite.c
    ${COMMON_DIR}/OD_helpers.c
    ${COMMON_DIR}/daemon_manager.c
    ${COMMON_DIR}/dbus_controller.c
    ${COMMON_DIR}/cpufreq.c
    ${COMMON_DIR}/board_info.c
    ${COMMON_DIR}/logind_interface.c
    ${SYSTEM_APPS_SOURCES}
    ${BOARD_APPS_SOURCES}
    src/main.c
)


##############################################################################
# Create an executable

add_executable(oresat-linux-manager ${SOURCE_FILES})

target_link_libraries(oresat-linux-manager CANopenNode)
target_link_libraries(oresat-linux-manager ${LIBSYSTEMD_LIBRARIES} Threads::Threads)

target_include_directories(oresat-linux-manager PRIVATE ${OLM_INCLUDE_DIRS})
target_include_directories(oresat-linux-manager PRIVATE ${LIBSYSTEMD_INCLUDE_DIRS})

target_compile_options(oresat-linux-manager PUBLIC ${LIBSYSTEMD_CFLAGS_OTHER})


############################################################
# Install

# Binaries
install(TARGETS oresat-linux-manager DESTINATION /usr/bin)

# Daemon service file
install(FILES oresat-linux-manager.service DESTINATION /lib/systemd/system)


##############################################################################
# Cpack debian package

if(${LINUX_DISTRIBUTION} MATCHES "Debian")
    set(CPACK_GENERATOR "DEB")
    set(CPACK_PACKAGE_VENDOR "PSAS")
    set(CPACK_COMPONENTS_ALL exe link config lastversion script log monitor)
    set(CPACK_PACKAGE_NAME ${PACKAGE_NAME})
    set(CPACK_PACKAGE_VERSION ${OLM_VERSION})
    set(CPACK_PACKAGE_CONTACT "rmedick@pdx.edu")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CANopen to Dbus interface for OreSat Linux boards")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsystemd-dev")
    set(CPACK_DEBIAN_PACKAGE_SECTION "embedded")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/oresat/oresat-linux-manager")
    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/debian/postinst" "${CMAKE_SOURCE_DIR}/debian/postrm" "${CMAKE_SOURCE_DIR}/debian/prerm")
    execute_process(COMMAND dpkg --print-architecture OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

    include(CPack)
endif()


if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree build, it is bad practice.\nTry 'cd build && cmake ..' instead.")
endif()

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(OreSat-Linux-Manager C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS "-DCO_VERSION_MAJOR=2 -DCO_DRIVER_CUSTOM=1 -DORESAT")
add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter)

##############################################################################
# Figure out which board

if(NOT BOARD)
    message(FATAL_ERROR 
        "No board specified\n"
        "ie: cmake -DBOARD=star-tracker ..\n"
        "Valid boards:\n"
        "   cfc\n"
        "   dxwifi\n"
        "   generic\n"
        "   gps\n"
        "   star-tracker\n"
        )
endif()

# ignore case
STRING(TOLOWER "${BOARD}" BOARD)

if(BOARD MATCHES "cirrus-flux-camera" OR BOARD MATCHES "cirrus_flux_camera" OR BOARD MATCHES "cfc")
    set(BOARD_NAME "Cirrus Flux Camera")
    set(BOARD_DIR "cirrus_flux_camera")
elseif(BOARD MATCHES "gps")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DTIME_PRODUCER")
    set(BOARD_NAME "GPS")
    set(BOARD_DIR "gps")
elseif(BOARD MATCHES "dxwifi")
    set(BOARD_NAME "DxWifi")
    set(BOARD_DIR "dxwifi")
elseif(BOARD MATCHES "star-tracker" OR BOARD MATCHES "star_tracker" OR BOARD MATCHES "st" OR BOARD MATCHES "startracker")
    set(BOARD_NAME "Star Tracker")
    set(BOARD_DIR "star_tracker")
elseif(BOARD MATCHES "generic")
    set(BOARD_NAME "Generic")
    set(BOARD_DIR "generic")
else()
    message(FATAL_ERROR "${BOARD} is not a valid board")
endif()

message(STATUS "${BOARD_NAME} board selected")

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
find_package(Doxygen)

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
# Check if make or ninja

if(CMAKE_MAKE_PROGRAM MATCHES "make")
    set(CMAKE_MAKE_PROGRAM_PRETTY_NAME "make")
elseif(CMAKE_MAKE_PROGRAM MATCHES "ninja")
    set(CMAKE_MAKE_PROGRAM_PRETTY_NAME "ninja")
else()
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
else()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)

##############################################################################
# Create an executable

add_executable(oresat-linux-manager src/main.c)

add_subdirectory(src)

target_link_libraries(oresat-linux-manager
    CANopenNode
    socketCAN
    object_dictionary
    common
    core
    manitory_apps
    daemons
    board
    ${LIBSYSTEMD_LIBRARIES}
    Threads::Threads
    )

target_include_directories(oresat-linux-manager PRIVATE ${LIBSYSTEMD_INCLUDE_DIRS})

target_compile_options(oresat-linux-manager PUBLIC ${LIBSYSTEMD_CFLAGS_OTHER})

# install
install(TARGETS oresat-linux-manager DESTINATION /usr/bin)
install(FILES oresat-linux-managerd.service DESTINATION /lib/systemd/system)

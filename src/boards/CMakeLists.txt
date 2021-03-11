
# common debian package feilds
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PSAS <oresat@pdx.edu>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsystemd-dev")
set(CPACK_DEBIAN_PACKAGE_SECTION "embedded")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/oresat/oresat-linux-manager")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/debian/postinst" "${CMAKE_SOURCE_DIR}/debian/postrm" "${CMAKE_SOURCE_DIR}/debian/prerm")
execute_process(COMMAND dpkg --print-architecture OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)

add_subdirectory(${BOARD_DIR})

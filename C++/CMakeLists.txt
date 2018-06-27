find_package(Boost REQUIRED)

include(${CMAKE_CURRENT_LIST_DIR}/CXXFlags.cmake)

add_library(getkw "")

target_sources(getkw
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Getkw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Section.cpp
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Getkw.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/GetkwError.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Keyword.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Section.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/messages.hpp>
    # FIXME Are these needed?
    $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/Getkw/Getkw.hpp>
    $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/Getkw/Getkw.hpp>
    $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/Getkw/GetkwError.hpp>
    $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/Getkw/Keyword.hpp>
    $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/Getkw/Section.hpp>
    $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}/Getkw/messages.hpp>
  )

target_compile_options(getkw
  PUBLIC
    "${GETKW_CXX_FLAGS}"
    "$<$<CONFIG:RELEASE>:${GETKW_CXX_FLAGS_RELEASE}>"
  PRIVATE
    "$<$<CONFIG:DEBUG>:${GETKW_CXX_FLAGS_DEBUG}>"
  )

target_include_directories(getkw
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}>
  )

target_link_libraries(getkw
  PUBLIC
    Boost::boost
  )

set_target_properties(getkw
  PROPERTIES
    CXX_STANDARD 11
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1
    MACOSX_RPATH ON
    PUBLIC_HEADER "Getkw.hpp;GetkwError.hpp;Keyword.hpp;Section.hpp;messages.hpp"
  )

install(
  TARGETS
    getkw
  EXPORT
    GetkwTargets
  ARCHIVE
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
  RUNTIME
    DESTINATION ${INSTALL_BINDIR}
    COMPONENT bin
  LIBRARY
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
  PUBLIC_HEADER
    DESTINATION ${INSTALL_INCLUDEDIR}/Getkw
    COMPONENT dev
  )

install(
  EXPORT
    GetkwTargets
  NAMESPACE
    "Getkw::"
  DESTINATION
    ${INSTALL_CMAKEDIR}
  COMPONENT
    dev
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/GetkwConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
  )

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/GetkwConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/GetkwConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CMAKEDIR}
  )

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/GetkwConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/GetkwConfigVersion.cmake
  DESTINATION
    ${INSTALL_CMAKEDIR}
  )

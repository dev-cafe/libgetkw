find_package(Boost REQUIRED)

include(${CMAKE_CURRENT_LIST_DIR}/CXXFlags.cmake)

add_library(getkw STATIC "")

list(APPEND _public_headers
   Getkw.hpp
   GetkwError.hpp
   Keyword.hpp
   Section.hpp
   messages.hpp
  )

# Copy headers to build-dir to mirror install-dir layout
foreach(_header IN LISTS _public_headers)
 file(
    COPY ${_header}
    DESTINATION ${PROJECT_BINARY_DIR}/${INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    )
endforeach()

target_sources(getkw
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Getkw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Section.cpp
  )

target_compile_definitions(getkw
  INTERFACE
    $<INSTALL_INTERFACE:USING_getkw>
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
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
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
    PUBLIC_HEADER "${_public_headers}"
  )

install(
  TARGETS
    getkw
  EXPORT
    getkwTargets
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
    DESTINATION ${INSTALL_INCLUDEDIR}/getkw
    COMPONENT dev
  )

install(
  EXPORT
    getkwTargets
  NAMESPACE
    "getkw::"
  DESTINATION
    ${INSTALL_CMAKEDIR}
  COMPONENT
    dev
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/getkwConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
  )

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/getkwConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/getkwConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CMAKEDIR}
  )

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/getkwConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/getkwConfigVersion.cmake
  DESTINATION
    ${INSTALL_CMAKEDIR}
  )

# Alias useful for use with FetchContent
add_library(getkw::getkw ALIAS getkw)

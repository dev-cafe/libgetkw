cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(getkw CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)

set(getkw_VERSION_MAJOR 1)
set(getkw_VERSION_MINOR 5)

include_directories("${PROJECT_BINARY_DIR}")

option(GETKW_C++_INTERFACE "Enable the C++ interface" ON)
option(GETKW_C_INTERFACE "Enable the C interface" OFF)
option(GETKW_Fortran_INTERFACE "Enable the Fortran interface" OFF)

if(GETKW_C++_INTERFACE)
  add_subdirectory(C++)
endif ()

if(GETKW_C_INTERFACE)
  enable_language(C)
  add_subdirectory(C)
endif ()

if(GETKW_Fortran_INTERFACE)
  enable_language(Fortran)
  add_subdirectory(Fortran)
endif ()

find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(docs
    COMMAND ${DOXYGEN_EXECUTABLE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

install(FILES Python/getkw.py
  DESTINATION lib/python2.7/site-packages
  )

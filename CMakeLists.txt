project(libgetkw C CXX Fortran)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_BUILD_TYPE Release)

set (libgetkw_VERSION_MAJOR 1)
set (libgetkw_VERSION_MINOR 5)

include_directories("${PROJECT_BINARY_DIR}")

option(GETKW_C++_INTERFACE "Enable the C++ interface" ON)
option(GETKW_C_INTERFACE "Enable the C interface" OFF)
option(GETKW_FORTRAN_INTERFACE "Enable the Fortran interface" OFF)

if (GETKW_C++_INTERFACE)
	add_subdirectory(C++)
endif (GETKW_C++_INTERFACE)

if (GETKW_C_INTERFACE)
	add_subdirectory(C)
endif (GETKW_C_INTERFACE)

if (GETKW_FORTRAN_INTERFACE)
	add_subdirectory(Fortran)
endif (GETKW_FORTRAN_INTERFACE)

#find_package(Doxygen)
#if (DOXYGEN_FOUND)
#	add_custom_target(docs 
#		COMMAND ${DOXYGEN_EXECUTABLE} 
#		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#		)
#endif(DOXYGEN_FOUND)

configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	)

install(FILES Python/getkw.py Python/pyparsing.py
	DESTINATION share/libgetkw
	)

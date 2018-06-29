#.rst:
#
# Decide which interfaces to build.
#
# Variables defined::
#
#   GETKW_CXX_INTERFACE
#   GETKW_C_INTERFACE
#   GETKW_Fortran_INTERFACE
#
# autocmake.yml configuration::
#
#   docopt:
#     - "--cxxgetkw=<GETKW_CXX_INTERFACE> Toggle C++ interface <ON/OFF> [default: ON]."
#     - "--cgetkw=<GETKW_C_INTERFACE> Toggle C interface <ON/OFF> [default: OFF]."
#     - "--fgetkw=<GETKW_Fortran_INTERFACE> Toggle Fortran interface <ON/OFF> [default: OFF]."
#   define:
#     - "'-DGETKW_CXX_INTERFACE={0}'.format(arguments['--cxxgetkw'])"
#     - "'-DGETKW_C_INTERFACE={0}'.format(arguments['--cgetkw'])"
#     - "'-DGETKW_Fortran_INTERFACE={0}'.format(arguments['--fgetkw'])"

option_with_print(GETKW_CXX_INTERFACE "Enable the C++ interface" ON)
option_with_print(GETKW_C_INTERFACE "Enable the C interface" OFF)
option_with_print(GETKW_Fortran_INTERFACE "Enable the Fortran interface" OFF)

set(getkw_VERSION 1.5.0)
set(getkw_VERSION_MAJOR 1)
set(getkw_VERSION_MINOR 5)
set(getkw_VERSION_PATCH 0)

set(PROJECT_VERSION 1.5.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 5)
set(PROJECT_VERSION_PATCH 0)

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKEDIR CMake)
else()
  set(DEF_INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKEDIR ${DEF_INSTALL_CMAKEDIR} CACHE PATH "Installation directory for CMake files")
set(INSTALL_PYMODDIR ${INSTALL_LIBDIR}/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/site-packages CACHE PATH "Installation directory for Python module")

if(GETKW_CXX_INTERFACE)
  add_subdirectory(C++)
endif ()

if(GETKW_C_INTERFACE)
  add_subdirectory(C)
endif ()

if(GETKW_Fortran_INTERFACE)
  add_subdirectory(Fortran)
endif ()

add_subdirectory(Python)

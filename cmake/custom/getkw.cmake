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

set(getkw_VERSION_MAJOR 1)
set(getkw_VERSION_MINOR 5)

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

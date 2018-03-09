enable_language(C)

option_with_print(BUILD_C_TEST "Build the C test program" OFF)

include(${CMAKE_CURRENT_SOURCE_DIR}/CFlags.cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(cgetkw
  getkw.c
  pygetkw.c
  )
set_target_properties(cgetkw
  PROPERTIES
    C_STANDARD 99
    C_EXTENSIONS OFF
    C_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1
  )
target_compile_options(cgetkw
  PRIVATE
    "${GETKW_C_FLAGS}"
    "$<$<CONFIG:DEBUG>:${GETKW_C_FLAGS_DEBUG}>"
    "$<$<CONFIG:RELEASE>:${GETKW_C_FLAGS_RELEASE}>"
  )
target_include_directories(cgetkw
  SYSTEM PUBLIC
    ${PYTHON_INLCUDE_DIRS}
  )
target_link_libraries(cgetkw
  PUBLIC
    ${PYTHON_LIBRARIES}
  )

install(
  TARGETS cgetkw
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(
  FILES getkw.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

if(BUILD_C_TEST)
  add_executable(getkw_test getkw_test.c)
  target_link_libraries(getkw_test cgetkw)
  set_target_properties(getkw_test
    PROPERTIES
      C_STANDARD 99
      C_EXTENSIONS OFF
      C_STANDARD_REQUIRED ON
    )
endif()

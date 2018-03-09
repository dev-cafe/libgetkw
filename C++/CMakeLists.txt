find_package(Boost REQUIRED)

include(${CMAKE_CURRENT_SOURCE_DIR}/CXXFlags.cmake)

add_library(getkw
  Getkw.cpp
  GetkwError.cpp
  Section.cpp
  messages.cpp
  )
set_target_properties(getkw
  PROPERTIES
    CXX_STANDARD 11
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1
  )
target_compile_options(getkw
  PRIVATE
    "${GETKW_CXX_FLAGS}"
    "$<$<CONFIG:DEBUG>:${GETKW_CXX_FLAGS_DEBUG}>"
    "$<$<CONFIG:RELEASE>:${GETKW_CXX_FLAGS_RELEASE}>"
  )
target_link_libraries(getkw
  PUBLIC
    Boost::boost
  )

install(
  TARGETS getkw
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

install(
  FILES Getkw.hpp Section.hpp Keyword.hpp GetkwError.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

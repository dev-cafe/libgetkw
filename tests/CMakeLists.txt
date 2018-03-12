add_executable(cxx_test cxx_test.cpp)
set_target_properties(cxx_test
  PROPERTIES
    CXX_STANDARD 11
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1
  )
target_link_libraries(cxx_test
  PRIVATE
    getkw
  )
target_compile_definitions(cxx_test
  PRIVATE
    BOOST_NO_EXCEPTIONS
  )
file(COPY @pcmsolver.inp DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_test(
  NAME
    read_parsed
  COMMAND
    ${PROJECT_BINARY_DIR}/bin/cxx_test
  WORKING_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin
  )

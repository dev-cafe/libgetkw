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

file(COPY @pcmsolver.inp DESTINATION ${getkw_BINARY_DIR}/${INSTALL_BINDIR})

add_test(
  NAME
    read_parsed
  COMMAND
    $<TARGET_FILE:cxx_test>
  WORKING_DIRECTORY
    ${getkw_BINARY_DIR}/bin
  )

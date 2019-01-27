option_with_default(ENABLE_TESTS "Enable testing" ON)

if(ENABLE_TESTS)
  enable_testing()
  include(CTest)
  add_subdirectory(tests) # This must come last!!
endif()

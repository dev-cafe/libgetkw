list(APPEND GETKW_C_FLAGS
  #"-fno-rtti"
  #"-fno-exceptions"
  )

list(APPEND GETKW_C_FLAGS_DEBUG
  "-Wall"
  "-Wextra"
  "-Wpedantic"
  "-Winit-self"
  "-Wuninitialized"
  "-Wmissing-declarations"
  "-Wwrite-strings"
  )
if(CMAKE_C_COMPILER_ID MATCHES Clang)
  list(APPEND GETKW_C_FLAGS_DEBUG
    "-Wdocumentation"
    )
endif()

list(APPEND GETKW_C_FLAGS_RELEASE
  #"-fno-rtti"
  #"-fno-exceptions"
  )

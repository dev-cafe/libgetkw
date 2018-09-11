list(APPEND GETKW_CXX_FLAGS
  #"-fno-exceptions"
  #"-fno-rtti"
  )

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  list(APPEND GETKW_CXX_FLAGS_DEBUG
    "/Wall"
    )
else()
  list(APPEND GETKW_CXX_FLAGS_DEBUG
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Winit-self"
    "-Woverloaded-virtual"
    "-Wuninitialized"
    "-Wmissing-declarations"
    "-Wwrite-strings"
    "-Weffc++"
    )
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  list(APPEND GETKW_CXX_FLAGS_DEBUG
    "-Wdocumentation"
    )
endif()

list(APPEND GETKW_CXX_FLAGS_RELEASE
  #"-fno-rtti"
  #"-fno-exceptions"
  )

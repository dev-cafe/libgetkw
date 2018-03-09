list(APPEND GETKW_Fortran_FLAGS
  "-fimplicit-none"
  "-fautomatic"
  "-fmax-errors=5"
  "-std=f2003"
  )

list(APPEND GETKW_Fortran_FLAGS_DEBUG
  "-fbacktrace"
  "-Wall"
  "-Wextra"
  "-Wpedantic"
  )

list(APPEND GETKW_Fortran_FLAGS_RELEASE
  "-funroll-all-loops"
  "-ftree-vectorize"
  )

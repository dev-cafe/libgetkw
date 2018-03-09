enable_language(Fortran)

add_library(fgetkw
  getkw.f90
  kinds.f90
  teletype.f90
  )
target_compile_options(fgetkw
  PRIVATE
    "${GETKW_Fortran_FLAGS}"
    "$<$<CONFIG:DEBUG>:${GETKW_Fortran_FLAGS_DEBUG}>"
    "$<$<CONFIG:RELEASE>:${GETKW_Fortran_FLAGS_RELEASE}>"
  )

install(
  TARGETS fgetkw
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

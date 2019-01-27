file(
  COPY
    ${CMAKE_CURRENT_LIST_DIR}/getkw.py
    ${CMAKE_CURRENT_LIST_DIR}/pyparsing.py
  DESTINATION
    ${INSTALL_PYMODDIR}
  )

install(
  FILES
    getkw.py
    pyparsing.py
  DESTINATION
    ${INSTALL_PYMODDIR}
  COMPONENT
    bin
  )

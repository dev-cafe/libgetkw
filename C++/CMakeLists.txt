add_library(getkw 
	Getkw.cpp
	GetkwError.cpp
	Section.cpp
	messages.cpp
	)

install(TARGETS getkw ARCHIVE DESTINATION lib)

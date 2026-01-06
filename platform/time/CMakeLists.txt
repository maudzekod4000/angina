add_library(time OBJECT)

target_sources(time
	PRIVATE
		WaitableTimer.cpp
	PUBLIC
		WaitableTimer.h
)

target_link_libraries(time
	PRIVATE
		project_options
)


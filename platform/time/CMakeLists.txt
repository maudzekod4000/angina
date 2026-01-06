add_library(time OBJECT)

target_sources(time
	PRIVATE
		WaitableTimer.cpp
	PUBLIC
		WaitableTimer.h
)

target_include_directories(time
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)


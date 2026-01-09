add_library(time OBJECT)

target_sources(time
	PRIVATE
		WaitableTimer.cpp
		Stopwatch.cpp
		Time.cpp
	PUBLIC
		WaitableTimer.h
		Stopwatch.h
		Time.h
)

target_include_directories(time
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(time
	PRIVATE
		project_options
)

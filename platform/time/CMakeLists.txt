add_library(platform_time OBJECT)

target_sources(platform_time
	PRIVATE
		FramePacer.cpp
	PUBLIC
		FramePacer.h
)

target_include_directories(platform_time
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(platform_time
	PRIVATE
		project_options
		core
)

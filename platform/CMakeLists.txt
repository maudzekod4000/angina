add_library(platform STATIC)

add_subdirectory(logging)
add_subdirectory(input)
add_subdirectory(time)
add_subdirectory(init)

target_link_libraries(platform
	PRIVATE
		logging
		input
		time
		init
		project_options
)

target_include_directories(platform
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_library(platform INTERFACE)

add_subdirectory(logging)
add_subdirectory(error)
add_subdirectory(input)
add_subdirectory(time)
add_subdirectory(init)

target_link_libraries(platform
	INTERFACE
		logging
		error
		input
		time
		init
)

target_include_directories(platform
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}
)


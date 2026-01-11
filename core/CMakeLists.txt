add_library(core STATIC)

add_subdirectory(time)
add_subdirectory(error)
add_subdirectory(units)

target_include_directories(core
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(core
	PRIVATE
		project_options
		time
		error
		units
)

add_library(error OBJECT)

target_sources(error
	PRIVATE
		Errors.ixx
)

target_include_directories(error
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(error
	PRIVATE
		project_options
)


add_library(rendering OBJECT)

target_sources(rendering
	PUBLIC
		Renderer.h
)

target_include_directories(rendering
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(rendering
	PRIVATE
		project_options
		core
)

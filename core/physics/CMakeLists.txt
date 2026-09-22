add_library(physics OBJECT)

target_sources(physics
	PRIVATE
		PhysicsUtils.cpp
	PUBLIC
		PhysicsUtils.h
)

target_include_directories(physics
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(physics
	PRIVATE
		project_options
)

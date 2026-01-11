add_library(system OBJECT)

target_sources(system
	PRIVATE
		System.cpp
	PUBLIC
		Updateable.h
)

target_include_directories(system
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(system
	PRIVATE
		project_options
)

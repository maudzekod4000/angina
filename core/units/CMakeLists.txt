add_library(units OBJECT)

target_sources(units
	PRIVATE
		Units.cpp
	PUBLIC
		Units.hpp
)

target_include_directories(units
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(units
	PRIVATE
		project_options
)

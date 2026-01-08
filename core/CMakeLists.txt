add_library(core OBJECT)

target_sources(core
	PUBLIC
		units/Units.hpp
    PRIVATE
        units/Units.cpp
)

target_include_directories(core
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(core
	PRIVATE
		project_options
)

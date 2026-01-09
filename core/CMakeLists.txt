add_library(core STATIC)

target_sources(core
	PUBLIC
		units/Units.hpp
		error/Errors.h
    PRIVATE
        units/Units.cpp
		error/Errors.cpp
)

target_include_directories(core
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(core
	PRIVATE
		project_options
)

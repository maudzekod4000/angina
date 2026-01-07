add_library(backend INTERFACE)

add_subdirectory(sdl)

target_link_libraries(backend
	INTERFACE
		sdl
)

target_include_directories(backend
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}
)


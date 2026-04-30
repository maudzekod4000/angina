add_library(engine_impl STATIC)

add_subdirectory(sdl)

target_link_libraries(engine_impl
	PRIVATE
		engine_sdl
)

target_include_directories(engine_impl
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

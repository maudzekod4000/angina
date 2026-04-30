add_library(engine_sdl OBJECT)

target_sources(engine_sdl
	PUBLIC
		SDLEngine.h
	PRIVATE
		SDLEngine.cpp
)

target_include_directories(engine_sdl
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(engine_sdl
	PRIVATE
		project_options
        engine
        sdl
)

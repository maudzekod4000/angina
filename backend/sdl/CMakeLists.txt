add_library(sdl OBJECT)

target_sources(sdl
	PRIVATE
		input/SDLInputEventManager.cpp
		init/SDLVideoLifecycleManager.cpp
		ui/SDLWindow.cpp
		resources/SDLCPUTextureResourceLoader.cpp
	PUBLIC
		input/SDLInputEventManager.h
		init/SDLVideoLifecycleManager.h
		ui/SDLWindow.h
		resources/SDLCPUTexture.h
		resources/SDLCPUTextureResourceLoader.h
)

target_include_directories(sdl
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

find_package(SDL2 REQUIRED)

if (WIN32)
	find_package(SDL2_IMAGE REQUIRED)
endif (WIN32)

if (UNIX)
	find_package(SDL2_image REQUIRED)
endif (UNIX)

if (UNIX)
	find_package(SDL2_ttf REQUIRED)
endif (UNIX)

if (WIN32)
	find_package(SDL2_TTF REQUIRED)
endif (WIN32)

if (WIN32)
	find_package(SDL2_MIXER REQUIRED)
endif (WIN32)

if (UNIX)
	find_package(SDL2_mixer REQUIRED)
endif (UNIX)

target_include_directories(sdl
	PRIVATE 
		${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${INTERFACE_INCLUDE_DIRECTORIES}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(sdl
	PRIVATE
		${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY}
		core
		project_options
		platform
)

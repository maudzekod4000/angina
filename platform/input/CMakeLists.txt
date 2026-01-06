add_library(input OBJECT)

target_sources(input
	PRIVATE
		BaseInputEventManager.cpp
		SDLInputEventManager.cpp
	PUBLIC
		BaseInputEventManager.h
		SDLInputEventManager.h
		IInputEventManager.h
)

target_include_directories(input
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(input
	PRIVATE
		project_options
)

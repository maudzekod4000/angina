add_library(backend INTERFACE)

add_subdirectory(sdl)

# THINK: Will the backend link all possible libraries? or we will have a flag
# during cmake generation to include only the needed libraries. 
target_link_libraries(backend
	INTERFACE
		sdl
)

target_include_directories(backend
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/..
)


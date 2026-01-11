add_library(ui OBJECT)

target_sources(ui
	PUBLIC
		window/IWindow.h
        window/WindowConfig.h
	PRIVATE
		window/WindowConfig.cpp
)

target_include_directories(ui
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(ui
	PRIVATE
		project_options
        core
)

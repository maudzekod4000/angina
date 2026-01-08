add_library(ui INTERFACE)

target_sources(ui
	INTERFACE
		window/IWindow.h
        window/WindowConfig.h
)

target_include_directories(ui
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(ui
	INTERFACE
		project_options
        core
)

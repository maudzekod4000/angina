add_library(init OBJECT)

target_sources(init
	PRIVATE
		SubsystemLifecycleManagers.cpp
	PUBLIC
		SubsystemLifecycleManagers.h
        ISubsystemLifecycleManager.h
)

target_include_directories(init
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(init
	PRIVATE
		project_options
		core
)


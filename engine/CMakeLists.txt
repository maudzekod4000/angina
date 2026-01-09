add_library(engine STATIC)

target_sources(engine
    PUBLIC
        Engine.h
        EngineConfig.h
        EngineState.h
    PRIVATE
        Engine.cpp
        EngineConfig.cpp
        EngineState.cpp
)

target_include_directories(engine
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(engine
    PRIVATE
        project_options
        core
        platform
        backend
)

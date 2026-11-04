add_library(engine STATIC)

target_sources(engine
    PUBLIC
        Engine.h
        EngineConfig.h
        EngineState.h
        GameObject.h
        Animation.h
        Movement.h
	    Collision.h
        MovementObservable.h
        MovementSystem.h
    PRIVATE
        Engine.cpp
        EngineConfig.cpp
        EngineState.cpp
        GameObject.cpp
        Animation.cpp
        Movement.cpp
	    Collision.cpp
        MovementObservable.cpp
        MovementSystem.cpp
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

add_library(logging OBJECT)

target_sources(logging
	PRIVATE
		ConsoleLogger.cpp
		DeduplicatingLogger.cpp
	PUBLIC
		ConsoleLogger.h
		DeduplicatingLogger.h
		ILogger.h
)

target_include_directories(logging
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(logging
	PRIVATE
		project_options
)

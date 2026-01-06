add_library(logging OBJECT)

target_sources(logging
	PRIVATE
		ConsoleLogger.cpp
	PUBLIC
		ConsoleLogger.h
		ILogger.h
)

target_include_directories(logging
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)


add_library(identity OBJECT)

target_sources(identity
	PRIVATE
		IdGenerator.cpp
	PUBLIC
		IdGenerator.h
		Id.h
)

target_include_directories(identity
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(identity
	PRIVATE
		project_options
)

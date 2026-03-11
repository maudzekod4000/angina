add_library(data_structures OBJECT)

target_sources(data_structures
	PRIVATE
		FreeList.cpp
	PUBLIC
		FreeList.h
)

target_include_directories(data_structures
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(data_structures
	PRIVATE
		project_options
		identity
)

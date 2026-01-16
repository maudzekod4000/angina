add_library(resources OBJECT)

target_sources(resources
	PRIVATE
		BaseResourceManager.cpp
	PUBLIC
		IResourceManager.h
		CPUTextureResourceLoader.h
		IResource.h
		CPUTexture.h
		CPUTextureHandle.h
)

target_include_directories(resources
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(resources
	PRIVATE
		project_options
		core
)

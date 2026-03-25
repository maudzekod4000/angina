#ifndef SDL_CPU_TEXTURE_LOADER_ASYNC_H
#define SDL_CPU_TEXTURE_LOADER_ASYNC_H

#include "platform/resources/CPUTextureResourceLoader.h"

#include "core/datastructures/FreeList.h"

namespace Backend::SDL::Resources {

/// Loads resources in parallel
class SDLCPUTextureLoaderAsync : public Platform::Resources::CPUTextureResourceLoader {
public:

	/// Empty implementation. Use SDLCPUTextureLoader::load method instead.
	Platform::Resources::IdOrError load(const std::filesystem::path& resourceFile) override;

	/// Thread-safe method for loading one or more resources in parallel. 
	std::vector<Platform::Resources::IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override;

	Platform::Resources::CPUTextureHandle resolve(Core::Identity::Id id) override;

	bool isValid(Core::Identity::Id id) override;
private:
	Core::DataStructures::FreeList<Platform::Resources::CPUTextureHandle> texHandleFreeList; ///< Actual storage of the CPU texture handles.
};

}

#endif // !SDL_CPU_TEXTURE_LOADER_ASYNC_H

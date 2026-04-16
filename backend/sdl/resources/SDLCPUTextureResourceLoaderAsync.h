#ifndef SDL_CPU_TEXTURE_LOADER_ASYNC_H
#define SDL_CPU_TEXTURE_LOADER_ASYNC_H

#include "platform/resources/CPUTextureResourceLoader.h"

#include "core/datastructures/FreeList.h"

namespace Backend::SDL::Resources {

/// Loads resources in parallel, but the load time will depend on the slowest texture
/// load, because we are blocking and waiting for all textures to be loaded,
/// before adding the textures to the freelist storage.
class SDLCPUTextureLoaderAsync : public Platform::Resources::CPUTextureResourceLoader<Platform::Resources::CPUTextureHandle> {
public:

	/// Empty implementation. Use SDLCPUTextureLoader::load method instead.
	Platform::Resources::IdOrError load(const std::filesystem::path& resourceFile) override;

	/// Thread-safe method for loading one or more resources in parallel. 
	std::vector<Platform::Resources::IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override;

	Platform::Resources::CPUTextureHandle resolve(Core::Identity::Id id) override;

	bool isValid(Core::Identity::Id id) override;

	/// I don't plan to use this class...
	/// But let us think. So this class is expected to be used from a single thread,
	/// Usually the main thread. So if you call load() and then isDone() the answer should
	/// always be isDone == true, because the load() method waits on all loads to complete
	/// before returning.
	bool isDone() const override;

	void wait() override;
private:
	Core::DataStructures::FreeList<Platform::Resources::CPUTextureHandle> texHandleFreeList; ///< Actual storage of the CPU texture handles.
};

}

#endif // !SDL_CPU_TEXTURE_LOADER_ASYNC_H

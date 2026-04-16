#ifndef SDL_CPU_TEXTURE_LOADER_HYPER_ASYNC
#define SDL_CPU_TEXTURE_LOADER_HYPER_ASYNC

#include <thread>

#include "platform/resources/CPUTextureResourceLoader.h"

#include "core/datastructures/FreeList.h"
#include "core/identity/IdGenerator.h"
#include "core/datastructures/RWProtected.h"
#include <platform/resources/CPUTextureHandle.h>

namespace Backend::SDL::Resources {

/// Loads resources in parallel and returns control immediately.
/// Textures will become available at their own time, whenever they are loaded.
/// Use isValid to check if the texture has been loaded and resolve to get a handle to it.
class SDLCPUTextureLoaderHyperAsync : public Platform::Resources::CPUTextureResourceLoader<Platform::Resources::CPUTextureHandle> {
public:

	/// Hmmmm this is interesting...So we have to return the Id before we added it to the 
	/// Freelist...that means that we must expand the freelist so that it can accept an Id
	/// We generate the Id and return it and then we use that same Id when we add to the
	/// freelist...
	Platform::Resources::IdOrError load(const std::filesystem::path& resourceFile) override;

	/// Thread-safe method for loading one or more resources in parallel. 
	std::vector<Platform::Resources::IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override;

	Platform::Resources::CPUTextureHandle resolve(Core::Identity::Id id) override;

	bool isValid(Core::Identity::Id id) override;

	/// This is not implemented. I think this class is wasting threads and
	/// I will probably not use it, so I don't think I will implement this method.
	bool isDone() const override;

	void wait() override;
private:
	Core::DataStructures::RWProtected<Core::DataStructures::FreeList<Platform::Resources::CPUTextureHandle>> texHandleFreeList; ///< Actual storage of the CPU texture handles.
	Core::Identity::IdGenerator idGenerator;
	std::vector<std::jthread> workerHandles;
};

}

#endif // !SDL_CPU_TEXTURE_LOADER_HYPER_ASYNC

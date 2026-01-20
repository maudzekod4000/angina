#ifndef BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H
#define BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

#include <unordered_map>
#include <expected>
#include <vector>
#include <stack>

#include "core/identity/IdGenerator.h"
#include "core/error/Errors.h"

#include "platform/resources/CPUTextureResourceLoader.h"

#include "SDLCPUTexture.h"

namespace Backend::SDL::Resources {

class SDLCPUTextureResourceLoader : public Platform::Resources::CPUTextureResourceLoader {
public:
	Platform::Resources::IdOrError load(const std::filesystem::path& resourceFile) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override;

	Platform::Resources::CPUTextureHandle resolve(Core::Identity::Id id) override;

	bool isValid(Core::Identity::Id id) override;
private:
	Core::Identity::IdGenerator idGenerator; ///< Used for generating ids for resources.

	std::vector<Platform::Resources::CPUTextureHandle> storage; ///< Actual storage of the CPU texture handles.
	std::unordered_map<Core::Identity::Id, size_t> idToIndexInStorage; ///< A mapping between an Id and an index in the storage of the actual handle object.
	std::stack<size_t> freeList; ///< A list of free indexes into the storage that can be reused. If it is empty, push to the end of storage, if not, use the first free index.
};

}

#endif // !BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

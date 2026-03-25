#ifndef BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H
#define BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

#include <expected>

#include "core/error/Errors.h"
#include "core/datastructures/FreeList.h"

#include "platform/resources/CPUTextureResourceLoader.h"

namespace Backend::SDL::Resources {

class SDLCPUTextureResourceLoader : public Platform::Resources::CPUTextureResourceLoader {
public:
	Platform::Resources::IdOrError load(const std::filesystem::path& resourceFile) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override;

	Platform::Resources::CPUTextureHandle resolve(Core::Identity::Id id) override;

	bool isValid(Core::Identity::Id id) override;
private:
	Core::DataStructures::FreeList<Platform::Resources::CPUTextureHandle> texHandleFreeList; ///< Actual storage of the CPU texture handles.
};

}

#endif // !BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

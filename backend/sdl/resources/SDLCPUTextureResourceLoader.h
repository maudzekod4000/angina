#ifndef BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H
#define BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

#include "core/error/Errors.h"
#include "core/datastructures/FreeList.h"

#include "platform/resources/CPUTextureResourceLoader.h"

namespace Backend::SDL::Resources {

/// Simple, sequential resource loader.
class SDLCPUTextureResourceLoader : public Platform::Resources::CPUTextureResourceLoader {
public:

	/// Does a synchronous, blocking load of a texture resource.
	Platform::Resources::IdOrError load(const std::filesystem::path& resourceFile) override;

	/// Does a synchronous, blocking load of one or many texture resources, one after the other,
	/// starting from the first in the list of paths.
	std::vector<Platform::Resources::IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override;

	Platform::Resources::CPUTextureHandle resolve(Core::Identity::Id id) override;

	bool isValid(Core::Identity::Id id) override;

	/// As this is a synchronous loader, this always returns true.
	/// This class is not expected to be used in a multithreaded context.
	bool isDone() const override;

	void wait() override;
private:
	Core::DataStructures::FreeList<Platform::Resources::CPUTextureHandle> texHandleFreeList; ///< Actual storage of the CPU texture handles.
};

}

#endif // !BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

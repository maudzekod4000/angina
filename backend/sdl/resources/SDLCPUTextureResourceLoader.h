#ifndef BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H
#define BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

#include <unordered_map>
#include <expected>

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
	std::unordered_map<Core::Identity::Id, Platform::Resources::CPUTextureHandle> textureHandlesIndex; ///< Keeps a mapping between an id and the corresponding texture.
};

}

#endif // !BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

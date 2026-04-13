#ifndef BACKEND_SDL_RESOURCES_GPU_TEXTURE_LOADER_H
#define BACKEND_SDL_RESOURCES_GPU_TEXTURE_LOADER_H

#include "platform/resources/CPUTextureResourceLoader.h"
#include "platform/resources/GPUTextureHandle.h"

namespace Backend::SDL::Resources {
class SDLGPUTextureLoader : public Platform::Resources::CPUTextureResourceLoader<Platform::Resources::GPUTextureHandle> {
public:
	Platform::Resources::IdOrError load(const std::filesystem::path& resourceFile) override {}

	std::vector<Platform::Resources::IdOrError> load(const std::vector<std::filesystem::path>& resourceFiles) override;

	Core::Errors::ErrorCode release(Core::Identity::Id id) override {}

	Platform::Resources::GPUTextureHandle resolve(Core::Identity::Id id) override {}

	bool isValid(Core::Identity::Id id) override {}

	bool isDone() const override {}

	void wait() override {}

private:
	Platform::Resources::CPUTextureResourceLoaderPtr cpuTexLoader;

};
}

#endif // !BACKEND_SDL_RESOURCES_GPU_TEXTURE_LOADER_H

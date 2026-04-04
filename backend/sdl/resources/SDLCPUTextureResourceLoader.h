#ifndef BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H
#define BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

#include "core/error/Errors.h"
#include "platform/resources/CPUTextureResourceLoaderWorker.h"

#include "platform/resources/CPUTextureResourceLoader.h"

namespace Backend::SDL::Resources {

/// Simple, sequential resource loader.
class SDLCPUTextureResourceLoader : public Platform::Resources::CPUTextureLoadWorker {
public:

	SDLCPUTextureResourceLoader();
};

}

#endif // !BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

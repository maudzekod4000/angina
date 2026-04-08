#ifndef BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H
#define BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

#include "platform/resources/CPUTextureResourceLoaderWorker.h"

namespace Backend::SDL::Resources {

class SDLCPUTextureResourceLoader : public Platform::Resources::CPUTextureLoadWorker {
public:
	SDLCPUTextureResourceLoader();
};

}

#endif // !BACKEND_SDL_SDL_CPU_TEXTURE_RESOURCE_LOADER_H

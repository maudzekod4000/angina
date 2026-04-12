#ifndef BACKEND_SDL_RENDERER_H
#define BACKEND_SDL_RENDERER_H

#include <expected>

#include "platform/rendering/Renderer.h"
#include "platform/resources/GPUTextureHandle.h"
#include "platform/resources/CPUTextureHandle.h"
#include "platform/resources/TextureTransferer.h"
#include "core/error/Errors.h"

struct SDL_Renderer;

namespace Backend::SDL::Rendering {
class SDLRenderer : public Platform::Rendering::Renderer, public Platform::Resources::TextureTransferer {
public:
	explicit SDLRenderer(SDL_Renderer*);
	void render(Platform::Resources::GPUTextureHandle) override;

	std::expected<Platform::Resources::GPUTextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(Platform::Resources::CPUTextureHandle) override;
private:
	SDL_Renderer* renderer = nullptr; ///< Received from the outside but managed by this class.
};
}

#endif // !BACKEND_SDL_RENDERER_H

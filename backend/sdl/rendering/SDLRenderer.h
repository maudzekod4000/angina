#ifndef BACKEND_SDL_RENDERER_H
#define BACKEND_SDL_RENDERER_H

#include <expected>

#include "platform/rendering/Renderer.h"
#include "platform/resources/TextureHandle.h"
#include "platform/resources/TextureTransferer.h"
#include "core/error/Errors.h"

struct SDL_Renderer;

namespace Backend::SDL::Rendering {
class SDLRenderer : public Platform::Rendering::Renderer, public Platform::Resources::TextureTransferer {
public:
	static std::unique_ptr<SDLRenderer> make(SDL_Renderer*);

	static std::shared_ptr<SDLRenderer> makeShared(SDL_Renderer*);

	void render(Platform::Resources::TextureHandle) override;

	std::expected<Platform::Resources::TextureHandle, Core::Errors::ErrorCode> convertCPUToGPUTexture(Platform::Resources::TextureHandle) override;
private:
	explicit SDLRenderer(SDL_Renderer*);

	SDL_Renderer* renderer = nullptr; ///< Received from the outside but managed by this class.
};

}

#endif // !BACKEND_SDL_RENDERER_H

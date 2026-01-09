#include "TextureRendererComponent.h"

#include "SDL_render.h"
#include "SDL_image.h"
#include "SDL_shape.h"

#include "enginev2/graphics/sdl/window/Window.h"
#include "enginev2/graphics/sdl/primitives/Texture.h"
#include "enginev2/graphics/models/Point.h"
#include "enginev2/graphics/models/Pixel.h"
#include "enginev2/graphics/models/Line.h"
#include "enginev2/graphics/animation/Sprite.h"
#include "enginev2/graphics/sdl/primitives/Rectangle.h"
#include "enginev2/models/GameObject.h"
#include "enginev2/debug/Debug.h"

void TextureRendererComponent::init(Window& window, const Color& clearColor) {
	// TODO: These hard-coded values should be made easily configurable.
	renderer = SDL_CreateRenderer( window.sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	if (!renderer) {
		DebugLog.showErrorInfo("loading renderer");
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	this->clearColor = clearColor;
}

void TextureRendererComponent::clear() {
	SDL_SetRenderDrawColor(renderer, clearColor.red, clearColor.green, clearColor.blue, 0xFF);
	SDL_RenderClear(renderer);
}

void TextureRendererComponent::render(Texture& texture) {
    SDL_Rect dest{0, 0, texture.dim.w, texture.dim.h};
    SDL_RenderCopyEx(renderer, texture.texture, nullptr, &dest, texture.rotation, nullptr, texture.flip);
}

void TextureRendererComponent::render(GameObject& obj) {
	if (!obj.sprite.atlas) {
		return;
	}
  SDL_Rect dest{obj.renderingPos.x, obj.renderingPos.y, obj.dim.w, obj.dim.h};
	SDL_Rect src{ 0, 0, obj.dim.w, obj.dim.h };
  SDL_RenderCopyEx(renderer, obj.sprite.atlas->texture, &src, &dest, NULL, nullptr, obj.sprite.atlas->flip);
}

void TextureRendererComponent::render(Texture& texture, Rectangle& viewPort) {
	SDL_RenderSetViewport(renderer, &viewPort.rect);
	render(texture);
}

void TextureRendererComponent::render(Rectangle& rect) {
	 SDL_SetRenderDrawColor(renderer, rect.color.red, rect.color.green, rect.color.blue, rect.color.alpha);

	 if (rect.fill) {
		 SDL_RenderFillRect(renderer, &rect.rect);
	 } else {
		 SDL_RenderDrawRect(renderer, &rect.rect);
	 }
}

void TextureRendererComponent::render(Pixel& pixel) {
	SDL_SetRenderDrawColor(renderer, pixel.color.red, pixel.color.green, pixel.color.blue, pixel.color.alpha);
	SDL_RenderDrawPoint(renderer, pixel.position.x, pixel.position.y);
}

void TextureRendererComponent::render(Line& line) {
	SDL_SetRenderDrawColor(renderer, line.color.red, line.color.green, line.color.blue, line.color.alpha);
	SDL_RenderDrawLine(renderer, line.a.x, line.a.y, line.b.x, line.b.y);
}

void TextureRendererComponent::render(Sprite& sprite)
{
	SDL_Rect& rect = sprite.frames[sprite.currentFrame].rect;
	SDL_Rect dest{ 0, 0, rect.w, rect.h };
	
	
	SDL_RenderCopyEx(renderer, sprite.atlas->texture, &rect, &dest, sprite.atlas->rotation, nullptr, sprite.atlas->flip);
}

void TextureRendererComponent::update() {
	SDL_RenderPresent(renderer);
}

SDL_Renderer* TextureRendererComponent::get() const
{
	return renderer;
}

void TextureRendererComponent::setClearColor(const Color& color)
{
	this->clearColor = color;
}

TextureRendererComponent::~TextureRendererComponent() {
	SDL_DestroyRenderer(renderer);
}

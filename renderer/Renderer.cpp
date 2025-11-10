#include "Renderer.h"

#include <iostream>
#include <utility>

#include "SDL_render.h"
#include "SDL_shape.h"

#include "platform/sdl/primitives/Texture.h"
#include "platform/sdl/primitives/Surface.h"
#include "renderer/shapes/Rect.h"
#include "platform/sdl/components/Window.h"
#include "renderer/primitives/Object.h"
#include "renderer/primitives/Button.h"

#include "exceptions/GraphicsInitException.h"

void Renderer::clear() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void Renderer::render(const Texture &texture) const {
	SDL_RenderCopy(renderer, texture.getTexture(), nullptr, nullptr);
}

void Renderer::render(Rect &rect) const {
	Color rectColor = rect.getColor();
	SDL_Rect rawRect = rect.getRawRect();

	SDL_SetRenderDrawColor(renderer, rectColor.red, rectColor.green,
			rectColor.blue, rectColor.alpha);
	SDL_RenderFillRect(renderer, &rawRect);
}

void Renderer::render(Object &object) const {
	Dimensions objectDimensions = object.getDimensions();
	Point objectPosition = object.getPosition();
	SDL_Rect rect = SDL_Rect { objectPosition.x, objectPosition.y,
			objectDimensions.w, objectDimensions.h };
	Point center = object.getCenter();
	SDL_Point sdlCenter = { center.x, center.y };

	SDL_RenderCopyEx(renderer, object.texture.getTexture(), nullptr, &rect,
			object.transformation.rotation, &sdlCenter,
			(SDL_RendererFlip) object.transformation.flip);
}

void Renderer::update() {
	SDL_RenderPresent(renderer);
}

Renderer::Renderer(Window &window) {
	init(window);
}

Renderer::~Renderer() {
	deinit();
}

void Renderer::init(Window &window) {
	renderer = SDL_CreateRenderer(window.getWindow(), -1,
			SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	std::cout << "Renderer initialised" << std::endl;
}

void Renderer::deinit() {
	SDL_DestroyRenderer(renderer);
	std::cout << "Renderer deinitialised" << std::endl;
}

Texture* Renderer::from(Surface &surface) const {
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,
			surface.getSurface());

	if (texture == nullptr) {
		throw GraphicsInitException(SDL_GetError());
	}

	Texture *t = new Texture(texture,
			{ surface.getSurface()->w, surface.getSurface()->h });

	delete &surface;

	return t;
}

std::vector<Texture*> Renderer::from(
		const std::vector<Surface*> &surfaces) const {
	std::vector<Texture*> textures;
	textures.reserve(surfaces.size());

	for (Surface *surface : surfaces) {
		textures.push_back(from(*surface));
	}

	return textures;
}

Object* Renderer::from(Texture &texture, Point p, Dimensions dim) const {
	return new Object(texture, dim, p);
}

Object* Renderer::fromSurface(Surface &surface, Point p, Dimensions dim) const {
	Texture *t = from(surface);

	return from(*t, p, dim);
}

Button* Renderer::from(Texture &texture) {
	return new Button(texture, Point::UNDEFINED, texture.getDimensions());
}

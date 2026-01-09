#include "Window.h"

#include <iostream>

#include "SDL.h"
#include "SDL_video.h"
#include "SDL_surface.h"

#include "platform/sdl/primitives/Surface.h"
#include "enginev2/graphics/models/Color.h"
#include "exceptions/BaseException.h"

Window::Window(): clearColor(SDL_Color{0xFF, 0xFF, 0xFF}), sdlWindow(nullptr), surface(nullptr) {}

void Window::init(const std::string& title,
		int32_t xPos,
		int32_t yPos,
		Width width,
		Height height) {
	sdlWindow = SDL_CreateWindow(
			title.c_str(),
			xPos,
			yPos,
			width.value,
			height.value,
			SDL_WINDOW_SHOWN
	);

	if (sdlWindow == nullptr) {
		throw BaseException(SDL_GetError());
	}

	std::cout << "Window initialised" << std::endl;
}

void Window::init(const std::string& title,
				Width width,
				Height height) {
	init(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height);
}

void Window::resize(Width width, Height height) {
	SDL_SetWindowSize(sdlWindow, width.value, height.value);
}

void Window::update() {
	SDL_UpdateWindowSurface(sdlWindow);
}

void Window::clear() {
	SDL_FillRect(surface, NULL, SDL_MapRGB( surface->format, clearColor.r, clearColor.g, clearColor.b ));
}

void Window::setClearColor(const Color& color)
{
	this->clearColor = { color.red, color.green, color.blue };
}

Window::~Window() {
	if (sdlWindow != nullptr) {
		SDL_DestroyWindow(sdlWindow);
		sdlWindow = nullptr;
	}

	std::cout << "Window destroyed" << std::endl;
}

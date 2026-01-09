#include "Surface.h"

#include <iostream>

#include "SDL_surface.h"
#include "SDL_image.h"

#include "exceptions/BaseException.h"

// This constructor should be removed.
// We should have factory methods.
Surface::Surface(const std::string& surfaceAssetPath): surface(nullptr) {
	surface = IMG_Load(surfaceAssetPath.c_str());

	// TODO: Handle with default image
	if (surface == nullptr) {
		throw BaseException(SDL_GetError());
	}
}

Surface::Surface(SDL_Surface* rawSurface): surface(rawSurface) {}

Surface::~Surface() {
	SDL_FreeSurface(surface);

	std::cout << "Surface destroyed" << std::endl;
}

#include "Texture.h"

#include <iostream>

#include "SDL_image.h"

Texture::Texture(SDL_Texture* tx):
    texture(tx),
    dim(Dimensions::UNDEFINED),
    rotation(0.0),
    flip(SDL_FLIP_NONE) {
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  dim.w = w;
  dim.h = h;
}

void Texture::modulateColor(const Color& clr) const {
    SDL_SetTextureColorMod(texture, clr.red, clr.green, clr.blue);
}

void Texture::activateBlend() const {
	 SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void Texture::setAlpha(uint8_t value) const {
	 SDL_SetTextureAlphaMod(texture, value);
}

void Texture::rotate(double angle) {
    rotation += angle;
}

void Texture::activateHFlip() {
    flip = SDL_FLIP_HORIZONTAL;
}

void Texture::activateVFlip() {
    flip = SDL_FLIP_VERTICAL;
}

Dimensions Texture::getDimensions() const
{
  return dim;
}

Texture::~Texture() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
    texture = nullptr;

    std::cout << "Texture destroyed" << std::endl;
  }
}

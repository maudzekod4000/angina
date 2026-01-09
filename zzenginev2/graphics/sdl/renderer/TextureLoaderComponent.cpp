#include "TextureLoaderComponent.h"

#include "SDL_render.h"
#include "SDL_image.h"

#include "enginev2/graphics/sdl/renderer/TextureRendererComponent.h"

SDL_Texture* TextureLoaderComponent::loadTexture(TextureRendererComponent& renderer, const std::string& resourcePath)
{
  return IMG_LoadTexture(renderer.get(), resourcePath.c_str());
}

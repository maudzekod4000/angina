#ifndef ENGINEV2_GRAPHICS_SDL_RENDERER_TEXTURELOADERCOMPONENT_H_
#define ENGINEV2_GRAPHICS_SDL_RENDERER_TEXTURELOADERCOMPONENT_H_

#include <string>

struct SDL_Texture;
class TextureRendererComponent;

namespace TextureLoaderComponent {
    SDL_Texture* loadTexture(TextureRendererComponent&, const std::string& resourcePath);
};

#endif /* ENGINEV2_GRAPHICS_SDL_RENDERER_TEXTURELOADERCOMPONENT_H_ */

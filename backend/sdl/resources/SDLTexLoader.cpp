#include "SDLTexLoader.h"

#include "backend/sdl/error/SDLError.h"

#include <assert.h>

#include "SDL_image.h"

using namespace Backend::SDL::Resources;
using namespace Core::Errors;
using namespace Backend::SDL::Error;

SDLTexture load(const char* filepath, SDL_Renderer* r, ErrorCode& err)
{
    assert(filepath);

    SDL_Surface* cpuRamTex = IMG_Load(filepath);

    if (!cpuRamTex) {
        err = makeErr(__FUNCTION__);
        return SDLTexture();
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(r, cpuRamTex);

    if (!tex) {
        err = makeErr(__FUNCTION__);
        return SDLTexture();
    }

    return SDLTexture(tex);
}

#include "SDLTexLoader.h"

#include "backend/sdl/error/SDLError.h"

#include <assert.h>

#include "SDL_image.h"

using namespace Backend::SDL::Resources;
using namespace Core::Errors;
using namespace Backend::SDL::Error;

SDLTexture load(const char* filepath, ErrorCode& err)
{
    assert(filepath);

    SDL_Surface* cpuRamTex = IMG_Load(filepath);

    if (!cpuRamTex) {
        err = makeErr(__FUNCTION__);
        return SDLTexture();
    }



    return SDLTexture();
}

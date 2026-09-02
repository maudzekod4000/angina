#include "SDLError.h"

#include "SDL_error.h"

using namespace Core::Errors;

ErrorCode Backend::SDL::Error::makeErr(const char* funcName)
{
	return ErrorCode(-3, SDL_GetError(), funcName);
}

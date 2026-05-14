#ifndef BACKEND_ERROR_SDL_ERROR_H
#define BACKEND_ERROR_SDL_ERROR_H

#include "core/error/Errors.h"

namespace Backend::SDL::Error {

Core::Errors::ErrorCode make(const char* funcName);

}

#endif // !BACKEND_ERROR_SDL_ERROR_H

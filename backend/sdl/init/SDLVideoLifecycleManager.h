#ifndef INIT_SDL_INITIALIZER_H
#define INIT_SDL_INITIALIZER_H

namespace Backend::SDL::Init {
	Core::Errors::ErrorCode initVideo(uint64_t flags);
	void destroyVideo();
}

#endif // !INIT_SDL_INITIALIZER_H

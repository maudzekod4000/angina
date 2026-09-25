#ifndef SDL_AUDIO_EFFECT_H
#define SDL_AUDIO_EFFECT_H

#include "core/error/Errors.h"

struct Mix_Chunk;

namespace Backend::SDL::Resources {
struct AudioEffect {
	AudioEffect() = default;
	AudioEffect(Mix_Chunk*);
// TODO: This will be similar to a SDLTexture - it will hold a pointer to
// Mix_Chunk and will have freeMem()

	void play();

	void stop();

	void freeMem();

	Mix_Chunk* audio = nullptr;

private:
	int channel = -1;
};

AudioEffect loadAudioEffect(const char* path, Core::Errors::ErrorCode&);

}

#endif // !SDL_AUDIO_EFFECT_H

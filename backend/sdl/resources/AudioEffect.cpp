#include "AudioEffect.h"

#include "backend/sdl/error/SDLError.h"
#include "backend/sdl/resources/SDLResourceUtils.h"

#include <cassert>

#include "SDL_mixer.h"

using namespace Backend::SDL::Resources;
using namespace Backend::SDL::Error;

AudioEffect::AudioEffect(Mix_Chunk* c): audio(c) {
	assert(c);
}

void AudioEffect::play()
{
	// TODO: THink: It might not be that straightforward...
	// I think the effects would interrupt each other....we have to think of a way
	// to play them repeatedly but smartly.
	channel = Mix_PlayChannel(channel, audio, -1);
}

void AudioEffect::stop()
{
	Mix_HaltChannel(channel);
}

void AudioEffect::freeMem() {
	Mix_FreeChunk(audio);
}

AudioEffect Backend::SDL::Resources::loadAudioEffect(const char* path, Core::Errors::ErrorCode& err)
{
	assert(path);
	const auto sdlRelPath = resolvePath(path);

	Mix_Chunk* audio = Mix_LoadWAV(sdlRelPath.string().c_str());

	if (!audio) {
		err = makeErr(__FUNCTION__);
		return AudioEffect();
	}

	return AudioEffect(audio);
}

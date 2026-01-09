#include "Audio.h"

#include <iostream>

#include "SDL_mixer.h"

namespace Audio {
	const int32_t sampleRate = 44100;
	const int32_t numberOfChannels = 2;
	const int32_t chunkSize = 2048;

	void boot() {
		if (Mix_OpenAudio(sampleRate, MIX_DEFAULT_FORMAT, numberOfChannels, chunkSize) < 0) {
			std::cerr << "Could not initialize audio. Degrading to no audio mode..." << std::endl;
		}
	}
	void shutdown() {
		Mix_Quit();
	}
};

#ifndef ENGINE_ANIMATION_H
#define ENGINE_ANIMATION_H

#include "core/time/Stopwatch.h"

namespace Angina::EngineV3 {

struct Animation {
	Animation(int frameCount): frameCount(frameCount) {}

	// Having the animation duration here allows us to change up the 
	// animation speed without creating a new Animation
	void start(int animDurMs);

	void stop();

	void update();

	int currentFrameIdx = 0;
private:
	int frameCount = 0;
	int durationMs = 0;
	Core::Time::Stopwatch clock;
};

}

#endif // !ENGINE_ANIMATION_H

#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include <chrono>
#include <cassert>

#include "backend/sdl/resources/SDLTexture.h"
#include "core/units/Units.hpp"
#include "core/time/Stopwatch.h"

namespace Angina::EngineV3 {
	struct SpriteAnim {

		SpriteAnim(int frameCount): frameCount(frameCount) {}
		
		// TODO: THink: Hmmm i think this kinda time interpolation
		// and the kind that will be used for movement might share similar properties
		// but lets see...

		// Having the animation duration here allows us to change up the 
		// animation speed without creating a new SpriteAnim
		void start(int animDurMs) {
			animDurationMs = animDurMs;
			animationStopwatch.reset();
		}

		void stop() {
			animDurationMs = 0;
		}

		void update() {
			if (animDurationMs == 0 || frameCount == 1) return;

			long long timeSinceStartMs = std::chrono::duration_cast<std::chrono::milliseconds>(animationStopwatch.elapsed()).count();

			float animProgressPercent = timeSinceStartMs / float(animDurationMs);
			float animPercentNormalized = animProgressPercent - int(animProgressPercent);
			currentFrameIdx = int(frameCount * animPercentNormalized);
		}

		int currentFrameIdx = 0;
	private:
		int frameCount = 0;
		int animDurationMs = 0;
		Core::Time::Stopwatch animationStopwatch;
	};

	struct GameObject {
		Backend::SDL::Resources::SDLTexture texture;
		int x, y, w, h;

		// TODO: To be honest, the game object should have a width and height...
		// semantically its more important that leaving the texture to determine the width and height of the 
		// game object...While we are just doing rendering this the current state is ok,
		// but when we start talking collisions we will be in a different ballgame.
	};
}

#endif // !ENGINE_GAME_OBJECT_H

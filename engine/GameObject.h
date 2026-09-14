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

		// We need:
		// 1. a way to start the animation
		// 2. a way to reset the animation
		// 3. a way to stop the animation
		
		// TODO: THink: Hmmm i think this kinda time interpolation
		// and the kind that will be used for movement might share similar properties
		// but lets see...

		// Having the animation duration here allows us to change up the 
		// animation speed without creating a new SpriteAnim
		void start(int animDurMs) {
			animDurationMs = animDurMs;
			animationStopwatch.reset();
			active = true;
		}

		void stop() {
			active = false;
		}

		void update() {
			assert(animDurationMs > 0);
			if (!active || frameCount == 1) return; // This is a single frame sprite, i.e. a normal texture.

			// TODO: Do some calculations to figure out the current frame based on the time that passed
			// between starting the animation and now.
			long long timeSinceStartMs = std::chrono::duration_cast<std::chrono::milliseconds>(animationStopwatch.elapsed()).count();

			float animProgressPercent = timeSinceStartMs / float(animDurationMs);
			float animPercentNormalized = animProgressPercent - int(animProgressPercent);
			currentFrameIdx = int(frameCount * animPercentNormalized);

			// TODO: I think this calculation can be optimized.
		}

		// Design:
		// we need to track when the animation started and how long it has been running
		// in order to figure out which frame to show in the case of multiple frames.
		// if there is just a single frame then we just show that frame.

		// We can create another constructor that will just set a single frame and will not deal
		// with any time management.

		// another important thing is that we need to be able to stop the animation.

		int currentFrameIdx = 0;
	private:
		bool active = false;
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

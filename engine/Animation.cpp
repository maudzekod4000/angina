#include "Animation.h"

#include <chrono>

using namespace Angina::EngineV3;

void Animation::start(int animDurMs) {
	durationMs = animDurMs;
	clock.reset();
}

void Animation::stop() {
	durationMs = 0;
}

void Animation::update() {
	if (durationMs == 0 || frameCount == 1) return;

	long long timeSinceStartMs = std::chrono::duration_cast<std::chrono::milliseconds>(clock.elapsed()).count();

	float animProgressPercent = timeSinceStartMs / float(durationMs);
	float animPercentNormalized = animProgressPercent - int(animProgressPercent);
	currentFrameIdx = int(frameCount * animPercentNormalized);
}

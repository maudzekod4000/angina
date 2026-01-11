#include "FramePacer.h"

#include <cassert>

#include "core/time/WaitableTimer.h"

using namespace Platform::Time;

FramePacer::FramePacer(const Core::Units::FPS& desiredFPS, const Core::Time::Stopwatch& globalClock) noexcept :
	globalClock(globalClock), start({}), desiredFPS(desiredFPS) {
	assert(&globalClock != nullptr);
}

std::chrono::nanoseconds FramePacer::startFrame() noexcept
{
	start = globalClock.elapsed();
	return start;
}

std::chrono::nanoseconds FramePacer::endFrame() noexcept
{
	const auto end = globalClock.elapsed();
	const auto workTime = end - start;
	const auto waitTime = desiredFPS.toNano() - workTime;
	Core::Time::WaitableTimer::wait(std::max(waitTime, std::chrono::nanoseconds{ 0 }));
	return end;
}

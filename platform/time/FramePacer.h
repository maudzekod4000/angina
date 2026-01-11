#ifndef CORE_FRAME_TIMER_H
#define CORE_FRAME_TIMER_H

#include <chrono>

#include "core/time/Stopwatch.h"
#include "core/units/Units.hpp"

namespace Platform::Time {

/// Measures the time between startFrame and endFrame calls
/// and stalls the current thread for (desiredFrameTime - workTime) in order to provide consistent frame times.
class FramePacer final {
public:

	/// @param desiredFPS The implementation will strive to achieve this frame refresh rate, but it will not be 100% accurate.
	/// @param globalClock Running clock is expected, i.e. 'reset' was called before passing it here.
	FramePacer(const Core::Units::FPS& desiredFPS, const Core::Time::Stopwatch& globalClock) noexcept;

	/// Records the time of the start of the frame.
	/// @return Returns the absolute time in nanoseconds since the start of the global clock of when the frame has started.
	std::chrono::nanoseconds startFrame() noexcept;

	/// Calculates the duration between start frame and end frame,
	/// i.e. measurement of time of the work that has been done for a single frame.
	/// Stalls the current thread for the difference in time between the desired frame time and the time it took to process a single frame.
	/// @return Returns the absolute time in nanoseconds since the start of the global clock of when the frame has ended.
	std::chrono::nanoseconds endFrame() noexcept;
private:
	const Core::Time::Stopwatch& globalClock; ///< Clock providing a steady tick.
	std::chrono::nanoseconds start; ///< Nanoseconds since start of the global clock. Marks the start of a frame.
	const Core::Units::FPS desiredFPS;
};

}

#endif // !CORE_FRAME_TIMER_H

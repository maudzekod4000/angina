#ifndef UTILS_TIME_WAITABLETIMER_H_
#define UTILS_TIME_WAITABLETIMER_H_

#include <cstdint>
#include <chrono>

namespace Core::Time {

/// Precise timer. Can be used for efficiently putting the execution thread to sleep.
namespace WaitableTimer {
	/// Sleep/Wait for the specified number of nanoseconds
	/// @param duration The duration to sleep in nanoseconds
	/// @return true if successful, false otherwise
	bool wait(std::chrono::nanoseconds duration) noexcept;
}

}

#endif /* UTILS_TIME_WAITABLETIMER_H_ */

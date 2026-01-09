#ifndef UTILS_TIME_WAITABLETIMER_H_
#define UTILS_TIME_WAITABLETIMER_H_

#include <cstdint>

namespace Angina::Platform {

/// Precise timer. Can be used for efficiently putting the execution thread to sleep.
namespace WaitableTimer {
	/// Sleep/Wait for the specified number of nanoseconds
	/// @param nanoseconds The duration to sleep in nanoseconds
	/// @return true if successful, false otherwise
	bool wait(uint64_t nanoseconds);
}

}

#endif /* UTILS_TIME_WAITABLETIMER_H_ */

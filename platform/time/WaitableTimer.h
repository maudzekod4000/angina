#ifndef UTILS_TIME_WAITABLETIMER_H_
#define UTILS_TIME_WAITABLETIMER_H_

#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#endif

class WaitableTimer {
public:
	WaitableTimer();
	~WaitableTimer();

	// Delete copy constructor and assignment operator
	WaitableTimer(const WaitableTimer&) = delete;
	WaitableTimer& operator=(const WaitableTimer&) = delete;

	/// Sleep for the specified number of nanoseconds
	/// @param nanoseconds The duration to sleep in nanoseconds
	/// @return true if successful, false otherwise
	bool sleepFor(int64_t nanoseconds);

	/// Check if the timer is valid
	/// @return true if the timer handle is valid, false otherwise
	bool isValid() const;

private:
#ifdef _WIN32
	HANDLE timerHandle;
#else
	// On non-Windows platforms, we don't need a handle
#endif
};

#endif /* UTILS_TIME_WAITABLETIMER_H_ */


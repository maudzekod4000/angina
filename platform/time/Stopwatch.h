// This class will have start and stop methods
// and stop() will receive the elapsed time.
#ifndef TIME_STOPWATCH_H
#define TIME_STOPWATCH_H

#include <chrono>

/// Measures the duration between two points in time/code.
/// Not thread-safe - call reset and elapsed from the same thread.
/// Note: If there are multithreaded cases of measuring time, extend/compose this class.
class Stopwatch final {
public:

	/// Resets the stopwatch from zero. The next call to elapsed() will measure time from the last reset() call.
	void reset();

	/// Measures the duration between the last reset call and now.
	/// @pre Must be called after reset().
	/// @return The duration in nanoseconds. If reset is not called previously, elapsed will return the duration from epoch until now.
	std::chrono::nanoseconds elapsed() const;

private:
	std::chrono::steady_clock::time_point start; ///< Time point of the last reset call. Initially, this is epoch time.
};

#endif // !TIME_STOPWATCH_H

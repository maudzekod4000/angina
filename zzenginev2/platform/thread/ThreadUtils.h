#ifndef UTILS_THREAD_THREADUTILS_H_
#define UTILS_THREAD_THREADUTILS_H_

#include <cstdint>

class ThreadUtils {
public:
	ThreadUtils() = delete;

	static void sleepFor(int64_t milliseconds);
};

#endif /* UTILS_THREAD_THREADUTILS_H_ */

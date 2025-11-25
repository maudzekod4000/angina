#ifndef UTILS_THREAD_THREADUTILS_H_
#define UTILS_THREAD_THREADUTILS_H_

#include <cstdint>

class ThreadUtils final {
public:
	ThreadUtils() = delete;

	static void sleepFor(int64_t nanoseconds);
};

#endif /* UTILS_THREAD_THREADUTILS_H_ */

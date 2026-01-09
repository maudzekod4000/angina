#ifndef PLATFORM_TIME_UTILS_H
#define PLATFORM_TIME_UTILS_H

#include <cstdint>
#include <chrono>

namespace TimeUtils {
	static uint64_t timestamp() {
		auto durationSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::milliseconds>(durationSinceEpoch).count();
	}
}

#endif // !PLATFORM_TIME_UTILS_H

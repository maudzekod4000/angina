#include <thread>

#include "ThreadUtils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <thread>
#endif

void ThreadUtils::sleepFor(int64_t milliseconds) {
#ifdef _WIN32
	Sleep(milliseconds);
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
#endif
}

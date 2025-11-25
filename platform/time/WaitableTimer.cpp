#include "WaitableTimer.h"

#ifdef _WIN32
#include <synchapi.h>
#else
#include <thread>
#include <chrono>
#endif

WaitableTimer::WaitableTimer() {
#ifdef _WIN32
	timerHandle = CreateWaitableTimer(NULL, TRUE, NULL);
#else
	// On non-Windows platforms, no handle needed
#endif
}

WaitableTimer::~WaitableTimer() {
#ifdef _WIN32
	if (timerHandle != NULL && timerHandle != INVALID_HANDLE_VALUE) {
		CloseHandle(timerHandle);
	}
#endif
}

bool WaitableTimer::isValid() const {
#ifdef _WIN32
	return timerHandle != NULL && timerHandle != INVALID_HANDLE_VALUE;
#else
	return true; // Always valid on non-Windows
#endif
}

bool WaitableTimer::sleepFor(int64_t nanoseconds) {
	if (nanoseconds <= 0) {
		return true;
	}

#ifdef _WIN32
	if (!isValid()) {
		return false;
	}

	// Convert ns to 100-ns intervals required by Windows API
	LARGE_INTEGER li;
	li.QuadPart = -(nanoseconds / 100);  // negative = relative time

	BOOL ok = SetWaitableTimer(timerHandle, &li, 0, NULL, NULL, FALSE);
	if (!ok) {
		return false;
	}

	DWORD result = WaitForSingleObject(timerHandle, INFINITE);

	if (result != WAIT_OBJECT_0) {
		return false;
	}

	return true;
#else
	// On non-Windows, use standard library
	std::this_thread::sleep_for(std::chrono::nanoseconds(nanoseconds));
	return true;
#endif
}


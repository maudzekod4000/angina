#include <thread>

#include "ThreadUtils.h"

#ifdef _WIN32
#include <windows.h>
#include <synchapi.h>
#else
#include <thread>
#endif

void ThreadUtils::sleepFor(int64_t nanoseconds) {
#ifdef _WIN32
	if (nanoseconds <= 0)
        return;

    HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (!timer) {
        // timer creation failed, nothing we can do
        return;
    }

    // Convert ns to 100-ns intervals required by Windows API
    LARGE_INTEGER li;
    li.QuadPart = -(nanoseconds / 100);  // negative = relative time

    BOOL ok = SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE);
    if (!ok) {
        // If it failed, clean up and abort
        CloseHandle(timer);
        return;
    }

    DWORD result = WaitForSingleObject(timer, INFINITE);

    // Always close handle before checking
    CloseHandle(timer);

    if (result != WAIT_OBJECT_0) {
        // timer failed or was interrupted
        // optional: handle error or fallback path
    }
#else
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
#endif
}

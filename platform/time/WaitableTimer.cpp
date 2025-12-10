#include "WaitableTimer.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <thread>
#endif

#include <chrono>

using namespace Angina::Platform;

namespace {

void timerSleep(double seconds, bool spin) {

#ifndef _WIN32
#	error TODO maybe implement with usleep/nanosleep?
#else
	// modified version of code from https://blat-blatnik.github.io/computerBear/making-accurate-sleep-function/
	// further reading https://randomascii.wordpress.com/2020/10/04/windows-timer-resolution-the-great-rule-change/
	using namespace std::chrono;

	// Unlike the original we use a local timer so it should work with threads.
	// More importantly we use the Ex API for better precision, otherwise I'm getting multiple ms of error in the timer interval (which would require a very long spin).
	HANDLE timer = CreateWaitableTimerEx(NULL, NULL, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_MODIFY_STATE | SYNCHRONIZE);
	if (timer) {
		// The high res sleep seems to be accurate up to about 0.5ms, so if we're spinning leave enough room not to overshoot the deadline,
		// otherwise use a smaller value that will give us less bias in the estimation (errors both negative and positive instead of only positive).
		double estimate = spin ? 0.0009 : 0.0004;
		double mean = estimate;
		double m2 = 0;
		int64_t count = 1;

		while (seconds - estimate > 1e-7) {
			double toWait = seconds - estimate;
			LARGE_INTEGER due;
			due.QuadPart = -int64_t(toWait * 1e7);
			auto start = high_resolution_clock::now();
			SetWaitableTimerEx(timer, &due, 0, NULL, NULL, NULL, 0);
			WaitForSingleObject(timer, INFINITE);
			auto end = high_resolution_clock::now();

			double observed = (end - start).count() / 1e9;
			seconds -= observed;

			++count;
			double error = observed - toWait;
			double delta = error - mean;
			mean += delta / count;
			m2 += delta * (error - mean);
			double stddev = sqrt(m2 / (count - 1));
			estimate = mean + stddev;
		}
		CloseHandle(timer);
	}

	if (spin) {
		auto start = high_resolution_clock::now();
		while ((high_resolution_clock::now() - start).count() / 1e9 < seconds);
	}
#endif
	/* test code, results are accurate on Win10 b19045 with spin and +- 0.5ms with no spin

	for (int i = 1; i <= 20; ++i) {
		double t = 0.00025 * i;
		const int numReps = 200;
		int64 elapsed[numReps];
		for (int spin = 0; spin <= 1; ++spin) {
			VR::ElapsedTimer timer;
			int64 sum = 0;
			for (int k = 0; k < numReps; ++k) {
				vrdx::timerSleep(t, spin);
				elapsed[i] = timer.sinceLast(VR::EP_NANO);
				sum += elapsed[i];
			}
			double avg = sum / double(numReps);
			app_logDev("%s target %.2fms >> average %.3fms", spin ? "  spin" : "nospin", t * 1000, avg / 1000000.0);
		}
	}

	*/
}
}

bool WaitableTimer::wait(int64_t nanoseconds) {
	if (nanoseconds <= 0) {
		return true;
	}

#ifdef _WIN32
	timerSleep(nanoseconds / 1e9, true);
	return true;
#else
	// On non-Windows, use standard library
	std::this_thread::sleep_for(std::chrono::nanoseconds(nanoseconds));
	return true;
#endif
}

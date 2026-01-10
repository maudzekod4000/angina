#include "Stopwatch.h"

#include <cassert>

void Stopwatch::reset()
{
    start = std::chrono::steady_clock::now();
}

std::chrono::nanoseconds Stopwatch::elapsed() const
{
    assert(start.time_since_epoch().count() > 0);

    const auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now - start);
}

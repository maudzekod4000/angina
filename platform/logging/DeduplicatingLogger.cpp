#include "DeduplicatingLogger.h"

using namespace Platform::Logging;

DeduplicatingLogger::DeduplicatingLogger(LoggerPtr inner, std::chrono::milliseconds cooldown)
    : inner(std::move(inner)), cooldown(cooldown)
{
}

void DeduplicatingLogger::log(Level level, std::string_view msg)
{
}

void DeduplicatingLogger::log(Level level, const Core::Errors::ErrorCode& err)
{
}

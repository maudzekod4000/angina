#ifndef LOGGING_DEDUPLICATING_LOGGER_H
#define LOGGING_DEDUPLICATING_LOGGER_H

#include "ILogger.h"

#include <chrono>
#include <string>
#include <unordered_map>

namespace Platform::Logging {

class DeduplicatingLogger : public ILogger {
public:
    explicit DeduplicatingLogger(LoggerPtr inner, std::chrono::milliseconds cooldown);
    void log(Level, std::string_view msg) override;
    void log(Level, const Core::Errors::ErrorCode&) override;
private:
    LoggerPtr inner;
    std::chrono::milliseconds cooldown;
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> lastSeen;
};

}

#endif // !LOGGING_DEDUPLICATING_LOGGER_H

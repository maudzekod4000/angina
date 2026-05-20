#ifndef LOGGING_CONSOLE_LOGGER_H
#define LOGGING_CONSOLE_LOGGER_H

#include "ILogger.h"

namespace Platform::Logging {

class ConsoleLogger : public ILogger {
public:
	void log(Level, std::string_view msg) override;
	void log(Level, const Core::Errors::ErrorCode&) override;
};

}

#endif // !LOGGING_CONSOLE_LOGGER_H

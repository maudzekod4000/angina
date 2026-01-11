#ifndef LOGGING_CONSOLE_LOGGER_H
#define LOGGING_CONSOLE_LOGGER_H

#include "ILogger.h"

namespace Platform::Logging {

class ConsoleLogger : public ILogger {
public:
	void log(Level, std::string_view msg) override;
};

}

#endif // !LOGGING_CONSOLE_LOGGER_H

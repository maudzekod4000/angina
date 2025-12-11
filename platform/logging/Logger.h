#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <memory>

#include "ILogger.h"

namespace Angina::Logging {
class Logger {
public:
	explicit Logger(std::shared_ptr<ILogger> loggerInstance) : logger(loggerInstance) {}

	std::shared_ptr<ILogger> getInstance() const { return logger; }
private:
	std::shared_ptr<ILogger> logger;
};
}

#endif // !LOGGING_LOGGER_H

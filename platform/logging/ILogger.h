#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <string_view>
#include <memory>

#include "core/error/Errors.h"

namespace Platform::Logging {

enum class Level {
	INFO,
	ERROR
};

class ILogger {
public:
	virtual ~ILogger() = default;
	virtual void log(Level, std::string_view msg) = 0;
	virtual void log(Level, const Core::Errors::ErrorCode&) = 0;
};

using LoggerPtr = std::unique_ptr<ILogger>;

}

#endif // !LOGGER_LOGGER_H

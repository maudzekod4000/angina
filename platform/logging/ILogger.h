#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <string_view>

namespace Angina::Logging {

enum class Level {
	INFO,
	ERROR
};

class ILogger {
public:
	virtual void log(Level, std::string_view msg) = 0;
};
}

#endif // !LOGGER_LOGGER_H

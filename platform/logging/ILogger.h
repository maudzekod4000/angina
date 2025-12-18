#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <string_view>
#include <memory>

namespace Angina::Logging {

enum class Level {
	INFO,
	ERROR
};

class ILogger {
public:
	virtual void log(Level, std::string_view msg) = 0;
};

using LoggerPtr = std::shared_ptr<ILogger>;

}

#endif // !LOGGER_LOGGER_H

#include "ConsoleLogger.h"

#include <cassert>
#include <iostream>
#include <format>

using namespace Angina::Logging;

void ConsoleLogger::log(Level lvl, std::string_view msg)
{
	switch (lvl) {
	case Level::INFO: {
		std::cout << std::format("INFO: {}\n", msg);
		break;
	}
	case Level::ERROR: {
		std::cerr << std::format("ERROR: {}\n", msg);
		break;
	}
	default: {
		assert(false);
		break;
	}
	}
}

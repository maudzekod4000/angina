#ifndef DEBUG_H
#define DEBUG_H

#include <string>

class Debug {
public:
	void showDebugInfo();
	void showErrorInfo(const std::string& action);
};

extern Debug DebugLog;

#endif // !DEBUG_H

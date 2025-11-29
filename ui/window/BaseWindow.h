#ifndef UI_BASE_WINDOW_H
#define UI_BASE_WINDOW_H

#include <ui/window/WindowConfig.h>

namespace Angina::UI {

class BaseWindow {
public:
	explicit BaseWindow(const WindowConfig& c) : config(c) {}

private:
	WindowConfig config;
};

}

#endif // !UI_BASE_WINDOW_H

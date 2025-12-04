#ifndef UI_BASE_WINDOW_H
#define UI_BASE_WINDOW_H

#include <ui/window/WindowConfig.h>

namespace Angina::UI {

class BaseWindow {
public:
	explicit BaseWindow(const WindowConfig& c) : config(c) {}
	virtual ~BaseWindow() = default;

	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	// Should we be able to std::move the Window?
	// I think it is a good idea because we can configure it from the outside and pass it into the engine
private:
	WindowConfig config;
};

}

#endif // !UI_BASE_WINDOW_H

#ifndef UI_BASE_WINDOW_H
#define UI_BASE_WINDOW_H

import errors;

#include <memory>

#include "WindowConfig.h"
#include "core/units/Units.hpp"

namespace Angina::UI {

class IWindow {
public:
	explicit IWindow(const WindowConfig& c): config(c) {}
	virtual ~IWindow() = default;

	IWindow(const IWindow&) = delete;
	IWindow& operator=(const IWindow&) = delete;

	// Should we be able to std::move the Window?
	// I think it is a good idea because we can configure it from the outside and pass it into the engine

	virtual Errors::ErrorCode resize(Units::Width w, Units::Height h) = 0;
protected:
	const WindowConfig config;
};

using WindowPtr = std::unique_ptr<IWindow>;

}

#endif // !UI_BASE_WINDOW_H

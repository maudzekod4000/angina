#ifndef UI_WINDOW_CONFIG_H
#define UI_WINDOW_CONFIG_H

#include <string>

#include "core/units/Units.hpp"

namespace Platform::UI {

struct WindowConfig {
	explicit constexpr WindowConfig(
		const std::string& title,
		Core::Units::AbsX x,
		Core::Units::AbsY y,
		Core::Units::Width width,
		Core::Units::Height height) :
		title(title), xPos(x), yPos(y), width(width), height(height) {}

	const std::string title;
	const Core::Units::AbsX xPos;
	const Core::Units::AbsY yPos;
	const Core::Units::Width width;
	const Core::Units::Height height;
};

}

#endif // !UI_WINDOW_CONFIG_H

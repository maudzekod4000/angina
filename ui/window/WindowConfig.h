#ifndef UI_WINDOW_CONFIG_H
#define UI_WINDOW_CONFIG_H

#include <string>

#include "core/units/Units.hpp"

namespace Angina::UI {

struct WindowConfig {
	explicit constexpr WindowConfig(const std::string& title, Units::AbsX x, Units::AbsY y, Units::Width width, Units::Height height) :
		title(title), xPos(x), yPos(y), width(width), height(height) {}

	const std::string title;
	const Units::AbsX xPos;
	const Units::AbsY yPos;
	const Units::Width width;
	const Units::Height height;
};

}

#endif // !UI_WINDOW_CONFIG_H

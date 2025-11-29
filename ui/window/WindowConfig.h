#ifndef UI_WINDOW_CONFIG_H
#define UI_WINDOW_CONFIG_H

#include <string>
#include <assert.h>

namespace Angina::UI {

struct WindowConfig {
	explicit WindowConfig(const std::string& title, int x, int y, int width, int height) :
		title(title), xPos(x), yPos(y), width(width), height(height) {
		assert(x > 0);
		assert(y > 0);
		assert(width > 0);
		assert(height > 0);
	}

	const std::string title;
	const int xPos = 0;
	const int yPos = 0;
	const int width = 0;
	const int height = 0;
};

}

#endif // !UI_WINDOW_CONFIG_H

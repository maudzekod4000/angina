#include "BaseButton.h"

BaseButton::BaseButton(Point pos, Dimensions dim, std::function<void(void)> clb) :
		callback(clb), position(pos), dimensions(dim) {
}

Point BaseButton::getPosition() const {
	return position;
}

Dimensions BaseButton::getDimensions() const {
	return dimensions;
}

std::function<void(void)> BaseButton::getCallback() const {
	return callback;
}

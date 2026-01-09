#include "RectTextButton.h"

#include <functional>

#include "renderer/Renderer.h"
#include "renderer/primitives/Object.h"
#include "renderer/primitives/Text.h"

RectTextButton::RectTextButton(Point p, Dimensions dim, Color backgroundColor,
		Text &t, std::function<void(void)> clb) :
		BaseButton(p, dim, clb), rect(Rect(p, dim, backgroundColor)), text(t) {
}

void RectTextButton::draw(Renderer &renderer) {
	renderer.render(rect);
	renderer.render(dynamic_cast<Object&>(text));
}

#ifndef ENGINE_COMPONENTS_BUTTONS_RECTTEXTBUTTON_H_
#define ENGINE_COMPONENTS_BUTTONS_RECTTEXTBUTTON_H_

#include <string>

#include "renderer/primitives/Point.h"
#include "renderer/primitives/Dimensions.h"
#include "renderer/primitives/Color.h"
#include "renderer/shapes/Rect.h"

#include "engine/components/buttons/BaseButton.h"

struct Text;
struct Renderer;

/**
 * A button made of a rectangle and a text.
 * Color of rectangle can be configured.
 */
class RectTextButton: public BaseButton {
public:
	RectTextButton(Point, Dimensions, Color, Text&, std::function<void(void)>);
	~RectTextButton() = default;

	void draw(Renderer&);
private:
	Rect rect;
	Text &text;
};

#endif /* ENGINE_COMPONENTS_BUTTONS_RECTTEXTBUTTON_H_ */

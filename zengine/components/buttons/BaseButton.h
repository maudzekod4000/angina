#ifndef ENGINE_COMPONENTS_BUTTONS_BASEBUTTON_H_
#define ENGINE_COMPONENTS_BUTTONS_BASEBUTTON_H_

#include <functional>

#include "renderer/drawable/Drawable.h"
#include "renderer/primitives/Point.h"
#include "renderer/primitives/Dimensions.h"

class BaseButton: public Drawable {
public:
	BaseButton(Point, Dimensions, std::function<void(void)> callback);
	virtual ~BaseButton() = default;

	void draw(Renderer&) = 0;

	Point getPosition() const;
	Dimensions getDimensions() const;
	std::function<void(void)> getCallback() const;
private:
	std::function<void(void)> callback;
	Point position;
	Dimensions dimensions;
};

#endif /* ENGINE_COMPONENTS_BUTTONS_BASEBUTTON_H_ */

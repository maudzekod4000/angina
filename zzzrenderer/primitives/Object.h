#ifndef SDL_ENGINE_OBJECT_OBJECT_H_
#define SDL_ENGINE_OBJECT_OBJECT_H_

#include <cstdint>
#include <functional>

#include "renderer/primitives/Point.h"
#include "renderer/shapes/Rect.h"
#include "renderer/drawable/Drawable.h"
#include "renderer/primitives/Dimensions.h"
#include "renderer/primitives/Transformation.h"

struct Texture;
struct Renderer;

class Object: public Drawable {
public:
	Object(Texture&, Dimensions, Point);
	Object(Texture&, Dimensions, Point, float velocity, Point dest);
	~Object();

	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;
	Object(Object&&) = delete;
	Object& operator=(Object&&) = delete;

	void draw(Renderer&);
	void move(const float x, const float y);
	void move(const Point& newPosition);

	void setClip(Rect);

	Point getPosition() const;
	Dimensions getDimensions() const;
	Point getCenter() const;
	Texture& getTexture();
	Transformation getTransformation() const;
	Rect getClip() const;

	float getVelocity() const;
	Object& setVelocity(float);

	Point getDestination() const;
	Object& setDestination(Point);
private:
	Texture &texture;
	Transformation transformation;
	Dimensions dim;
	Point point;
	Point center;
	Rect clip;
	float velocity;
	Point destination;
};

#endif /* SDL_ENGINE_OBJECT_OBJECT_H_ */

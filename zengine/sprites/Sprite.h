#ifndef ENGINE_SPRITE_H_
#define ENGINE_SPRITE_H_

#include <cstdint>
#include <vector>

struct Object;
struct Rect;

/**
 * Handles sprite transitions. Useful when you have a sprite that contains the states for a single character/something in your game and
 * you want to define transitions for it.
 */
class Sprite {
public:
	Sprite(Object&, std::vector<Rect> states);

	/*
	 * Transitions to next state;
	 */
	void next();
private:
	Object& wrappedObject;
	int32_t currentState;
	std::vector<Rect> transitions;
};

#endif /* ENGINE_SPRITE_H_ */

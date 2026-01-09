#include "Sprite.h"

#include "renderer/primitives/Object.h"

Sprite::Sprite(Object& obj, std::vector<Rect> states)
	: wrappedObject(obj), currentState(0), transitions(states) {

	next();
}

void Sprite::next() {
	wrappedObject.setClip(transitions[currentState % (transitions.size() - 1)]);
	currentState++;
}

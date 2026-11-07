#include "BasicMovement.h"

using namespace Angina::EngineV3;
using namespace Core::Units;

void BasicMovement::move(const Core::Units::Vec2& dir, float step)
{
	dest = addVec(pos, scale(dir, step));
	// One option is to add a timer and reset it here - in update, if enough time passed without the move() being called
	// then we can emit a End

	// Another option would be to check if the destination is different from the current pos
	// if it is, then  there were no move() calls between the update calls so we can call End callback

	direction = dir;
}

void BasicMovement::update()
{
	if (pos.eq(dest)) {
		// then we can emit end...but ...how to make sure we emit it only once hah....
		if (onEnd) {
			onEnd();
		}
		return;
	}

	pos = dest;

	if (onStart) {
		onStart();
	}
}

void BasicMovement::stop()
{
	dest = pos;
}

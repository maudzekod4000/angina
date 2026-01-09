#include "MovementCmpt.h"

#include "platform/time/TimeUtils.h"
#include "enginev2/models/GameObject.h"

void MovementCmpt::move(GameObject& obj, Point& destination)
{
	uint64_t now = TimeUtils::timestamp();
	Point dir{ destination.x - obj.placementPos.x, destination.y - obj.placementPos.y };
	float dist = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));
	float timeToDest = dist / obj.speedFactor;
	MovementCmd cmd{ obj.placementPos, dir, now, timeToDest };
	movingObjects[obj.id] = std::make_pair(
		&obj,
		cmd
	);
}

void MovementCmpt::update()
{
	for (auto& entry : movingObjects) {
		updatePosition(entry.second.first, entry.second.second); // Yuck...fix this at some point...
	}
}

void MovementCmpt::stop(ID id)
{
}

void MovementCmpt::updatePosition(GameObject* gameObjPtr, const MovementCmd& cmd)
{
	uint64_t now = TimeUtils::timestamp();
	float diffS = (now - cmd.startTime) / 1000.f;
	float movementScale = diffS / cmd.timeToDest;
	if (movementScale > 1) {
		// TODO: We could delete the entry in the map, but it's not a big deal.
		return;
	}
	float newX = cmd.direction.x * movementScale;
	float newY = cmd.direction.y * movementScale;
	Point scaledDirVec = Point(static_cast<int32_t>(newX), static_cast<int32_t>(newY));
	Point newPos{ cmd.startPos.x + scaledDirVec.x, cmd.startPos.y + scaledDirVec.y };
	gameObjPtr->updateDirection(cmd.direction);
	gameObjPtr->updatePosition(newPos, Direction::NONE);
}

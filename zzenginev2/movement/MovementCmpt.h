#ifndef MOVEMENT_CMPT_H
#define MOVEMENT_CMPT_H

#include <unordered_map>
#include <utility>
#include <memory>
#include <cstdint>

#include "enginev2/components/ID.h"
#include "enginev2/graphics/models/Point.h"

class GameObject;

struct MovementCmd {
	Point startPos;
	Point direction;
	uint64_t startTime;
	float timeToDest;
};

class MovementCmpt {
public:
	void move(GameObject&, Point& destination);

	void update();

	void stop(ID id);
private:
	std::unordered_map<ID, std::pair<GameObject*, MovementCmd>> movingObjects;

	void updatePosition(GameObject*, const MovementCmd& cmd);
};

#endif // !MOVEMENT_CMPT_H

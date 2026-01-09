#ifndef ENGINE_MOVEMENT_LINEARFIXEDMOVEMENTMANAGER_H_
#define ENGINE_MOVEMENT_LINEARFIXEDMOVEMENTMANAGER_H_

#include <list>
#include <cstdint>

#include "renderer/primitives/Object.h"

class LinearFixedMovementManager {
public:
	LinearFixedMovementManager();

	void addMoveable(Object&);

	void processFrame(int64_t elapsedTime);
private:
	std::list<Object*> moveables;

	void processMoveable(Object&, int64_t elapsedTimeMicro);
};

#endif /* ENGINE_MOVEMENT_LINEARFIXEDMOVEMENTMANAGER_H_ */

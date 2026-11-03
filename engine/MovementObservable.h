#ifndef ENGINE_MOVEMENT_OBSERVABLE_H
#define ENGINE_MOVEMENT_OBSERVABLE_H

#include <functional>
#include <vector>

namespace Angina::EngineV3 {

enum class MovementEventType {
	START,
	STOP
};

struct MovementEvent {
	int id;
	MovementEventType type;
};

using MovementEventHandler = std::function<void(MovementEvent)>;

// What needs to be different if we want to async. notify the listeners?
class MovementObservable {
public:
	void registerHandler(MovementEventHandler);
	void update(MovementEvent);
private:
	std::vector<MovementEventHandler> handlers;
};
}

#endif // !ENGINE_MOVEMENT_OBSERVABLE_H

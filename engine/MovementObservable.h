#ifndef ENGINE_MOVEMENT_OBSERVABLE_H
#define ENGINE_MOVEMENT_OBSERVABLE_H

#include <functional>
#include <vector>

namespace Angina::EngineV3 {

enum class EventType {
	START,
	STOP
};

struct Event {
	int id;
	EventType type;
};

using EventHandler = std::function<void(Event)>;

// What needs to be different if we want to async. notify the listeners?
class Observable {
public:
	void registerHandler(EventHandler);
	void update(Event);
private:
	std::vector<EventHandler> handlers;
};
}

#endif // !ENGINE_MOVEMENT_OBSERVABLE_H

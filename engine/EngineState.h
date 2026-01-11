#ifndef V3_ENGINE_STATE_H
#define V3_ENGINE_STATE_H

#include <atomic>

namespace Angina::EngineV3 {

class EngineState final {
public:
	enum class State {
		UNINITIALIZED,
		INITIALIZING,
		RUNNING,
		STOPPING,
		STOPPED
	};

	EngineState();
	~EngineState() = default;

	// Delete copy constructor and assignment operator
	EngineState(const EngineState&) = delete;
	EngineState& operator=(const EngineState&) = delete;

	/// Get the current state atomically
	/// @return The current engine state
	State get() const;

	/// Set the state atomically
	/// @param state The new state to set
	void set(State state);

	bool isRunning() const;

private:
	std::atomic<State> currentState;
};

}

#endif /* V3_ENGINE_STATE_H */


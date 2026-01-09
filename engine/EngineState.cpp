#include "EngineState.h"

using namespace Angina::EngineV3;

EngineState::EngineState() : currentState(State::UNINITIALIZED) {
}

EngineState::State EngineState::get() const {
	return currentState.load(std::memory_order_acquire);
}

void EngineState::set(State state) {
	currentState.store(state, std::memory_order_release);
}

bool EngineState::isRunning() const
{
	return get() == State::RUNNING;
}

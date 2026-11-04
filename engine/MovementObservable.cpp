#include "MovementObservable.h"

using namespace Angina::EngineV3;

void Observable::registerHandler(EventHandler e)
{
	handlers.push_back(e);
}

void Observable::update(Event e)
{
	for (const auto& h : handlers) {
		h(e);
	}
}

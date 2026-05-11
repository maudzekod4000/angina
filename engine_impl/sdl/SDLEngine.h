#ifndef ENGINE_IMPL_SDL_ENGINE_H
#define ENGINE_IMPL_SDL_ENGINE_H

#include "engine/Engine.h"
#include "core/units/Units.hpp"

namespace EngineImpl::SDL {

class SDLEngine : public Angina::EngineV3::Engine {
public:
	explicit SDLEngine(const Platform::UI::WindowConfig&, Core::Units::RatePerSecond desiredFPS);
};
}

#endif // !ENGINE_IMPL_SDL_ENGINE_H

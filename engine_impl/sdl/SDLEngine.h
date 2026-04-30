#ifndef ENGINE_IMPL_SDL_ENGINE_H
#define ENGINE_IMPL_SDL_ENGINE_H

#include "engine/Engine.h"

namespace EngineImpl::SDL {

class SDLEngine : public Angina::EngineV3::Engine {
public:
	explicit SDLEngine();
};
}

#endif // !ENGINE_IMPL_SDL_ENGINE_H

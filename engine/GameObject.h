#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "backend/sdl/resources/SDLTexture.h"
#include "core/units/Units.hpp"

namespace Angina::EngineV3 {
	struct GameObject {
		Backend::SDL::Resources::SDLTexture texture;
		Core::Units::AbsPosition x, y;
	};
}

#endif // !ENGINE_GAME_OBJECT_H

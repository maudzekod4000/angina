#ifndef ENGINE_GAME_OBJECT_H
#define ENGINE_GAME_OBJECT_H

#include "backend/sdl/resources/SDLTexture.h"
#include "core/units/Units.hpp"

namespace Angina::EngineV3 {
	struct SpriteTexFrame {
		Backend::SDL::Resources::SDLTexture texture;
		Core::Units::Rect texSrc; // Cropping.
	};

	struct GameObject {
		SpriteTexFrame sprite;
		Core::Units::AbsPosition x, y;
	};
}

#endif // !ENGINE_GAME_OBJECT_H

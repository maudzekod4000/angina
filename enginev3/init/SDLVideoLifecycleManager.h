#ifndef INIT_SDL_INITIALIZER_H
#define INIT_SDL_INITIALIZER_H

#include "ISubsystemLifecycleManager.h"

namespace Angina::Init {
class SDLVideoLifecycleManager final : public ISubsystemLifecycleManager {
public:
	std::expected<void, Errors::ErrorCode> init(uint64_t flags) override;
	std::expected<void, Errors::ErrorCode> destroy() override;
};
}

#endif // !INIT_SDL_INITIALIZER_H

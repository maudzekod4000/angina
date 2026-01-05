#ifndef INIT_SDL_INITIALIZER_H
#define INIT_SDL_INITIALIZER_H

#include "ISubsystemLifecycleManager.h"

namespace Angina::Init {
class SDLVideoLifecycleManager final : public ISubsystemLifecycleManager {
public:
	Errors::ErrorCode init(uint64_t flags) override;
	Errors::ErrorCode destroy() override;
	bool isCriticalSubsystem() override;
};
}

#endif // !INIT_SDL_INITIALIZER_H

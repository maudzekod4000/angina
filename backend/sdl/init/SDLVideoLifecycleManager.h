#ifndef INIT_SDL_INITIALIZER_H
#define INIT_SDL_INITIALIZER_H

#include "platform/init/ISubsystemLifecycleManager.h"

namespace Backend::SDL::Init {
class SDLVideoLifecycleManager final : public Platform::Init::ISubsystemLifecycleManager {
public:
	Core::Errors::ErrorCode init(uint64_t flags) override;
	Core::Errors::ErrorCode destroy() override;
	bool isCriticalSubsystem() override;
};
}

#endif // !INIT_SDL_INITIALIZER_H

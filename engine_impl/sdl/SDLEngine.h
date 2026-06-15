#ifndef ENGINE_IMPL_SDL_ENGINE_H
#define ENGINE_IMPL_SDL_ENGINE_H

#include "engine/Engine.h"
#include "core/units/Units.hpp"

namespace EngineImpl::SDL {

class SDLEngine : public Angina::EngineV3::Engine {
public:
	explicit SDLEngine(const Platform::UI::WindowConfig&, Core::Units::RatePerSecond desiredFPS);
private:
	struct Resources {
		Platform::Init::SubsystemLifecycleManagersPtr slms;
		Platform::Logging::LoggerPtr logger;
		Platform::UI::WindowPtr window;
		Platform::Input::InputEventManagerPtr inputMgr;
		Platform::Rendering::RendererPtr renderer;
		Platform::Resources::TextureResourceLoaderPtr texLoader;
	};
	static Resources build(const Platform::UI::WindowConfig&);
	explicit SDLEngine(Resources, Core::Units::RatePerSecond);
};

}

#endif // !ENGINE_IMPL_SDL_ENGINE_H

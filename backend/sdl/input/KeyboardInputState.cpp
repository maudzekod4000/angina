#include "KeyboardInputState.h"

#include "SDL_events.h"

using namespace Backend::SDL::Input;

static_assert(Keys::Right == SDL_SCANCODE_RIGHT, "Keys::Right must match SDL_SCANCODE_RIGHT");
static_assert(Keys::Left == SDL_SCANCODE_LEFT, "Keys::Left must match SDL_SCANCODE_LEFT");

void KeyboardInputState::processEvent(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_KEYDOWN: {
		// Holding a key makes the OS send repeated KEYDOWN events;
		// those must not count as new presses.
		if (event.key.repeat) {
			break;
		}

		const int key = event.key.keysym.scancode;
		m_heldKeys.insert(key);
		m_pressedKeys.insert(key);
		break;
	}
	case SDL_KEYUP: {
		const int key = event.key.keysym.scancode;
		m_heldKeys.erase(key);
		m_releasedKeys.insert(key);
		break;
	}
	case SDL_WINDOWEVENT:
		// If the window loses focus while a key is held we never get its KEYUP,
		// so drop everything to avoid 'stuck' keys.
		if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
			m_heldKeys.clear();
		}
		break;
	default:
		break;
	}
}

bool KeyboardInputState::isKeyDown(int key) const
{
	return m_heldKeys.contains(key);
}

bool KeyboardInputState::isKeyPressed(int key) const
{
	return m_pressedKeys.contains(key);
}

bool KeyboardInputState::isKeyReleased(int key) const
{
	return m_releasedKeys.contains(key);
}

void KeyboardInputState::beginFrame()
{
	m_pressedKeys.clear();
	m_releasedKeys.clear();
}

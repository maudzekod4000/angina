#ifndef BACKEND_SDL_KEYBOARD_INPUT_STATE_H
#define BACKEND_SDL_KEYBOARD_INPUT_STATE_H

#include <unordered_set>

union SDL_Event;

namespace Backend::SDL::Input {

/// Key codes clients pass to KeyboardInputState.
/// Values are hardcoded so clients don't depend on SDL headers;
/// the .cpp static_asserts they match the SDL scancodes.
namespace Keys {
	constexpr int Right = 79;
	constexpr int Left = 80;
	constexpr int Space = 44;
}

/// Tracks keyboard state across frames so game code can poll it instead of reacting to callbacks.
/// Usage per frame:
///   1. beginFrame()            - clears the one-frame 'pressed'/'released' sets.
///   2. processEvent(e)         - for every SDL event polled this frame.
///   3. isKeyDown/Pressed/Released queries from game code.
class KeyboardInputState {
public:
	void processEvent(const SDL_Event& event);

	/// True for every frame the key is held.
	bool isKeyDown(int key) const;
	/// True only on the frame the key went down (OS key-repeat is ignored).
	bool isKeyPressed(int key) const;
	/// True only on the frame the key went up.
	bool isKeyReleased(int key) const;

	void beginFrame();

private:
	std::unordered_set<int> m_heldKeys;
	std::unordered_set<int> m_pressedKeys;
	std::unordered_set<int> m_releasedKeys;
};

}

#endif // !BACKEND_SDL_KEYBOARD_INPUT_STATE_H

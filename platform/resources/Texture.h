#ifndef RESOURCES_TEXTURE_H
#define RESOURCES_TEXTURE_H

namespace Platform::Resources {

/// Hmm, maybe i want to go with a simpler C-inspired design for this engine.
/// I feel the OOP things getting complex and we won't have two implementations
/// ever because this will be a concrete game.
/// so there will be a thin wrapper around the SDL_Texture that will 
/// hold the pointer, be able to delete things and also cache the width and height.
struct Texture {
	virtual ~Texture() {}

	virtual int width() const { return 0; }

	virtual int height() const { return 0; }
};

}

#endif // !RESOURCES_TEXTURE_H

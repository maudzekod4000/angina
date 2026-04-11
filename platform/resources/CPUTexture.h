#ifndef RESOURCES_TEXTURE_H
#define RESOURCES_TEXTURE_H

namespace Platform::Resources {

/// Common logic for CPU texture in-memory representation.
/// Hmmm...Idk if we should have CPUTexture and GPUTexture...
/// Maybe a class Texture would be enough as a base.
class CPUTexture {
public:
	virtual ~CPUTexture() = default;
};

}

#endif // !RESOURCES_TEXTURE_H

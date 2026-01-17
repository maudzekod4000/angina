#ifndef RESOURCES_TEXTURE_H
#define RESOURCES_TEXTURE_H

namespace Platform::Resources {

/// Common logic for CPU texture in-memory representation.
class CPUTexture {
public:
	virtual ~CPUTexture() = default;
};

}

#endif // !RESOURCES_TEXTURE_H

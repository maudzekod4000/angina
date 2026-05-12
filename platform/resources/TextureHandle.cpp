#include "TextureHandle.h"

using namespace Platform::Resources;

TextureHandle::TextureHandle(Texture* ptr) noexcept : ptr(ptr) {}

void TextureHandle::freeMem() {
	if (ptr) {
		delete ptr;
		ptr = nullptr;
	}
}

#ifndef SDL_GRAPHICS_GRAPHICS_H_
#define SDL_GRAPHICS_GRAPHICS_H_

class Graphics {
public:
	~Graphics();

	void init();
private:
	void boot();
	void bootImageExtension();
	void bootTTFExtensions();
	void shutdown();
};

#endif /* SDL_GRAPHICS_GRAPHICS_H_ */

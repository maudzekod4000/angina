#ifndef RESOURCES_RESOURCE_HANDLE_H
#define RESOURCES_RESOURCE_HANDLE_H

namespace Platform::Resources {

// The idea is that this class can be a handle to anything that is a pointer somewhere in memory.
// But at the same time we want to be typesafe, i.e. no void

template<typename ResourcePtrType>
class ResourceHandle {
	ResourcePtrType* ptr = nullptr; ///< Pointer to the resource.
	bool isReady = false; ///< Is the resource loaded.
	// TODO: There is a concept of 'generations' but i am still not familiar with it.
};

}

#endif // !RESOURCES_RESOURCE_HANDLE_H

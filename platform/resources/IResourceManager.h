#ifndef RESOURCES_IRESOURCE_MANAGER_H
#define RESOURCES_IRESOURCE_MANAGER_H

#include <filesystem>


// TODO: Some prerequisites for this class to work:
// 1. A thread-safe id generation class.
// 2. Something like a thread pool? Otherwise we will have logic for spawning workers...OR we could just spawn a thread on demand...not that bad for starters.

// Notes: We should be able to request multiple or single resources and this class should be fully async.
// And i suppose we must have a GPU resource manager that will query whether the CPU manager has finished its job and load the resources to the GPU.
// So basically the GPU manager has to find any changes in the CPU manager (loads or deletes) and apply them on the GPU too...
// But lets not forget that we might have audio resources or other types too...
// Lets make this interface generic - for both texture and audio and then we can make more concrete interfaces.
// It would be hard to make the interfaces of CPU and GPU loaders to match...maybe the GPU loader will be its own beast that checks for changes and uploads to GPU.
// Hah...a very good idea .... the CPU loader can generate a synchronized queue of changes (requests, deletions, etc) and the GPU loader would execute them.
namespace Platform::Resources {

class IResourceManager {
public:
	virtual ~IResourceManager() = default;


};

}
#endif // !RESOURCES_IRESOURCE_MANAGER_H

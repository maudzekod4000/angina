#ifndef IDENTITY_ID_GENERATOR_H
#define IDENTITY_ID_GENERATOR_H

#include <atomic>

#include "Id.h"

namespace Core::Identity {

// Generation of ids for resources, entities, objects.
// Monotonic and thread-safe.
class IdGenerator final {
public:
	/// Returns the current value of the monotonic counter and increments the counter.
	Id next() noexcept;
private:
	std::atomic<Id> id = 0; ///< This value will be incremented on each 'next' call. On overflow, the counter will start again from 0.
};

}

#endif // !IDENTITY_ID_GENERATOR_H

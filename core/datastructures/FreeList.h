#ifndef DS_FREE_LIST_H
#define DS_FREE_LIST_H

#include <vector>
#include <stack>
#include <unordered_map>
#include <concepts>
#include <assert.h>

#include "core/identity/Id.h"
#include "core/identity/IdGenerator.h"

namespace Core::DataStructures {

template <typename T>
concept HasFreeMem = requires(T t) {
	{ t.freeMem() };
};
// Vector with reusable indexes. Instead of growing with use, slots which are freed are reused.
// @tparam T Type of the value in storage. It is adviceable this type to be cheap for copy.
// The type should have a freeMem method if there is memory that needs to be freed when the item is erased from the freelist.
template <HasFreeMem T>
class FreeList {
public:
	/// Checks whether a item identified with this Id is in the list.
	/// @param id The id we want to query.
	/// @return True if the item exists in the list.
	bool has(Core::Identity::Id id) const {
		return idToIndexInStorage.find(id) != idToIndexInStorage.cend();
	}

	/// Finds and returns a copy of the item from storage.
	/// Always call 'has' first to check if the item exists, otherwise an empty object will be returned.
	/// @param id The id of the item we want to get.
	/// @return Returns the item from storage or an empty, default-constructed object if the item does not exist.
	T get(Core::Identity::Id id) const {
		assert(has(id));
		auto it = idToIndexInStorage.find(id);
		const size_t idx = it->second;
		return storage[idx];
	}

	Core::Identity::Id add(T item) {
		const Core::Identity::Id texId = idGenerator.next();
	
		if (freeList.size() > 0) {
			const size_t idx = freeList.top();
			freeList.pop();
			storage[idx] = std::move(item);
			idToIndexInStorage[texId] = idx;
		}
		else {
			storage.push_back(std::move(item));
			idToIndexInStorage[texId] = storage.size() - 1;
		}

		return texId;
	}

	/// Calls the freeMem method on the value associated with this id and free the index in storage so it can be reused.
	/// Make sure to call 'has(id)' before calling this method.
	/// @param id The id of the item we want to delete.
	void remove(Core::Identity::Id id) {
		assert(has(id));

		auto it = idToIndexInStorage.find(id);
		const size_t idx = it->second;
		T item = storage[idx];

		item.freeMem();

		idToIndexInStorage.erase(it);

		freeList.push(idx);
	}

	/// Returns the number of addressable/active/not-deleted elements in storage.
	size_t size() const {
		return idToIndexInStorage.size();
	}

	/// Returns the current storage size.
	/// Due to reuse mechanism, the size should remain somewhat flat when we have
	/// alternating add and remove operations.
	size_t storageSize() const {
		return storage.size();
	}

	size_t freeListSize() const {
		return freeList.size();
	}
private:
	std::vector<T> storage; ///< Actual storage of where the objects 'live'.
	std::unordered_map<Core::Identity::Id, size_t> idToIndexInStorage; ///< A mapping between an Id and an index in storage.
	std::stack<size_t> freeList; ///< A list of free indexes into the storage that can be reused. If it is empty, push to the end of storage, if not, use the first free index.
	Core::Identity::IdGenerator idGenerator; ///< Used for generating ids for resources.
};

}

#endif // !DS_FREE_LIST_H

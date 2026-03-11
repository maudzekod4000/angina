#ifndef DS_FREE_LIST_H
#define DS_FREE_LIST_H

#include <vector>
#include <stack>
#include <unordered_map>

#include "identity/Id.h"

namespace Core::DataStructures {

// Vector with reusable indexes. Instead of growing with use, slots which are considered free
// are reused. Hm....this list will be kinda tied to the Id but thats not so bad, an id is just a number.
// We want the T type to be a value type....it should be safe and cheap to copy.
template <typename T>
class FreeList {
public:
	// find(Id) -> how to create a custom iterator....that would allow us to have one method for both 'exist' and 'get'
	// free(Id)
	// add(T) -> decided whether to use the freelist or add at the end.
	// Hmmm or maybe have two methods -> find and get...because idk how to create a custom iterator.
	
	/// Checks whether a item identified with this Id is in the list.
	/// @param id The id we want to query.
	/// @return True if the item exists in the list.
	bool has(Core::Identity::Id id) const;

	/// Finds and returns a copy of the item from storage.
	/// Always call 'has' first to check if the item exists, otherwise an empty object will be returned.
	/// @param id The id of the item we want to get.
	/// @return Returns the item from storage or an empty, default-constructed object if the item does not exist.
	T get(Core::Identity::Id id) const;

	// TODO: Maybe a move semantic to avoid a copy? Usually we wont need the temporary value that
	// has been passed.
	Core::Identity::Id add(T item);

	bool remove(Core::Identity::Id id);
private:
	std::vector<T> storage; ///< Actual storage of where the objects 'live'.
	std::unordered_map<Core::Identity::Id, size_t> idToIndexInStorage; ///< A mapping between an Id and an index in storage.
	std::stack<size_t> freeList; ///< A list of free indexes into the storage that can be reused. If it is empty, push to the end of storage, if not, use the first free index.
};

}

#endif // !DS_FREE_LIST_H

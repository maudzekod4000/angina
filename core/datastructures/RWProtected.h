#ifndef DATA_STRUCTURES_RW_PROTECTED_H
#define DATA_STRUCTURES_RW_PROTECTED_H

#include <shared_mutex>

namespace Core::DataStructures {

/// Wrapper for values and containers that have distinct read and write access patterns.
/// Provides thread-safety for individual operations. Don't use for combined operations,
/// for example, for lookup and write, etc. because the mutex is not upgradable.
/// For custom operations, write your own implementation of thread synchrnoization
/// around the value or container.
/// The most common use case is, for example, if we have a std::vector and we 
/// want to pair it with a mutex and lock for operations like push_back (write)
/// or accessing by index (read). If we use this pattern often, the synch. code gets repetitive.
/// Instead, wrap the std::vector in this class and do the required operation within the callable.
/// @tparam Protectee A value or a container of values that will be synchronized.
/// Note: This approach is speeding up development, but I think it has greater overhead
/// at runtime than just wrapping the concrete API with a copy of each public method and 
/// adding synchrnoization...For now, the performance hit is not measured and probably not 
/// a bottleneck. And we are free to implement our own synchronization where needed.
template<typename Protectee>
class RWProtected {
public:

	/// Synchronization wrapper around read operations.
	/// Make sure the operation that you wrap in the Callable is a read operation.
	/// @tparam Callable The callable object, usually a lambda, which wraps the actual read operation.
	/// @return Returns whatever the wrapped callable returns. The return type is deduced during template instantiation.
	template<typename Callable>
	decltype(auto) read(Callable&& f) const
	{
		std::shared_lock lock(mutex);
		return std::forward<Callable>(f)(protectee);
	}

	/// Synchronization wrapper around write operations.
	/// Make sure the operation that you wrap in the Callable is a write operation.
	/// @tparam Callable The callable object, usually a lambda, which wraps the actual write operation.
	/// @return Returns whatever the wrapped callable returns. The return type is deduced during template instantiation.
	template<typename Callable>
	decltype(auto) write(Callable&& f)
	{
		std::unique_lock lock(mutex);
		return std::forward<Callable>(f)(protectee);
	}
private:
	mutable std::shared_mutex mutex;
	Protectee protectee; ///< Most often, this is a container that has read and write operations.
};
}

#endif // !DATA_STRUCTURES_RW_PROTECTED_H

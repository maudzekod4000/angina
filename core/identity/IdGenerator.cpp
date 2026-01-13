#include "IdGenerator.h"

using namespace Core::Identity;

Id IdGenerator::next() noexcept
{
	return id.exchange(id + 1ULL);
}

#include "BaseException.h"

BaseException::BaseException(std::string msg) :
		std::runtime_error(msg) {
}

std::ostream& operator<<(std::ostream &os, const std::runtime_error &ex) {
	os << ex.what();
	return os;
}

#ifndef EXCEPTIONS_BASEEXCEPTION_H_
#define EXCEPTIONS_BASEEXCEPTION_H_

#include <stdexcept>
#include <iostream>

class BaseException: public std::runtime_error {
public:
	BaseException(std::string msg);

	friend std::ostream& operator<<(std::ostream&, const std::runtime_error&);
};

#endif /* EXCEPTIONS_BASEEXCEPTION_H_ */

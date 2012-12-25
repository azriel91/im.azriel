/*
 * Exception.cpp
 *
 *  Created on: 11/12/2012
 *      Author: Azriel
 */

#include "im/azriel/common/exception/Exception.h"

namespace im {
namespace azriel {
namespace common {
namespace exception {

Exception::Exception(const char* message) : message(message) {
}

Exception::~Exception() throw() {
}

void Exception::printMessage() const throw() {
	fprintf(stderr, "%s: %s\n", typeid(*this).name(), this->message);
}

const char* Exception::what() const throw() {
	return this->message;
}

} /* namespace exception */
} /* namespace common */
} /* namespace azriel */
} /* namespace im */

/*
 * Exception.h
 *
 *  Created on: 11/12/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_COMMON_EXCEPTION__EXCEPTION_H_
#define __IM_AZRIEL_COMMON_EXCEPTION__EXCEPTION_H_

#include <exception>
#include <cstdio>
#include <typeinfo>

using namespace std;

namespace im {
namespace azriel {
namespace common {
namespace exception {

class Exception : public std::exception {
protected:
	/**
	 * The message for this exception.
	 */
	const char* message;

public:
	/**
	 * Construct an exception.
	 *
	 * @param message the message for this exception
	 */
	Exception(const char* message);
	virtual ~Exception() throw();
	/**
	 * Prints this exception's message to std::err with its typeid.
	 */
	void printMessage() const throw();
	/**
	 * Get the message for this exception.
	 *
	 * @return the message
	 */
	virtual const char* what() const throw();
};

} /* namespace exception */
} /* namespace common */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_COMMON_EXCEPTION__EXCEPTION_H_ */

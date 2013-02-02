/*
 * ControlKeyEvent.cpp
 *
 *  Created on: 1/01/2013
 *      Author: Azriel
 */

#include "im/azriel/heroquest/input/ControlKeyEvent.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

ControlKeyEvent::ControlKeyEvent(const ControlKeyInputSource* const source, const int code) :
		code(code),
		source(source) {
}

ControlKeyEvent::~ControlKeyEvent() {
	// we don't delete the source object
}

const int ControlKeyEvent::getCode() const {
	return this->code;
}

const ControlKeyInputSource* ControlKeyEvent::getSource() const {
	return this->source;
}

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

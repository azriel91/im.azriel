/*
 * KeyboardSynchronizedControlKeyInputSource.cpp
 *
 *  Created on: 1/04/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/input/keyboard/KeyboardSynchronizedControlKeyInputSource.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace input {
namespace keyboard {

KeyboardSynchronizedControlKeyInputSource::KeyboardSynchronizedControlKeyInputSource(const int* const keyCodes) :
		KeyboardControlKeyInputSource(keyCodes) {
}

KeyboardSynchronizedControlKeyInputSource::~KeyboardSynchronizedControlKeyInputSource() {
}

void KeyboardSynchronizedControlKeyInputSource::setControlKeyEnabled(const int code, const bool enabled) {
	SynchronizedControlKeyInputSource::setControlKeyEnabled(code, enabled);
}

} /* namespace keyboard */
} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

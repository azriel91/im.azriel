/*
 * KeyboardSynchronizedControlKeyInputSource.h
 *
 *  Created on: 1/04/2013
 *      Author: azriel
 */

#ifndef KEYBOARDSYNCHRONIZEDCONTROLKEYINPUTSOURCE_H_
#define KEYBOARDSYNCHRONIZEDCONTROLKEYINPUTSOURCE_H_

#include "im/azriel/heroquest/input/SynchronizedControlKeyInputSource.h"
#include "im/azriel/heroquest/input/keyboard/KeyboardControlKeyInputSource.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace input {
namespace keyboard {

class KeyboardSynchronizedControlKeyInputSource: public KeyboardControlKeyInputSource,
        public SynchronizedControlKeyInputSource {
public:
	KeyboardSynchronizedControlKeyInputSource(const int* const keyCodes);
	virtual ~KeyboardSynchronizedControlKeyInputSource();

protected:
	/**
	 * Sets the specified control key's enabled state.
	 *
	 * @param code the control key code
	 * @param enabled the state of the control key
	 */
	void setControlKeyEnabled(const int code, const bool enabled);
};

} /* namespace keyboard */
} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* KEYBOARDSYNCHRONIZEDCONTROLKEYINPUTSOURCE_H_ */

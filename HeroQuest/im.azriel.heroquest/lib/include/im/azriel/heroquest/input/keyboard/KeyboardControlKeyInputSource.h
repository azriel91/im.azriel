/*
 * KeyboardControlKeyInputSource.h
 *
 *  Created on: 30/03/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_INPUT__KEYBOARDCONTROLKEYINPUTSOURCE_H_
#define __IM_AZRIEL_HEROQUEST_INPUT__KEYBOARDCONTROLKEYINPUTSOURCE_H_

#include <cstring>

#include "im/azriel/heroquest/input/ControlKeyCode.h"
#include "im/azriel/heroquest/input/ControlKeyInputSource.h"

using namespace im::azriel::heroquest::input;

namespace im {
namespace azriel {
namespace heroquest {
namespace input {
namespace keyboard {

class KeyboardControlKeyInputSource: public ControlKeyInputSource {
private:
	/**
	 * The keyboard key codes that correspond to the control key codes.
	 */
	const int* const keyCodes;

public:
	/**
	 * Construct a KeyboardControlKeyInputSource with the passed in keyboard key codes to use as the control keys.
	 *
	 * @param keyCodes the key codes that correspond to the control keys
	 */
	KeyboardControlKeyInputSource(const int* const keyCodes);
	virtual ~KeyboardControlKeyInputSource();
	/**
	 * Called when a key is pressed on the keyboard.
	 *
	 * @param keyCode the key code of the key that was pressed
	 */
	void keyPressed(const int keyCode);
	/**
	 * Called when a key is released on the keyboard.
	 *
	 * @param keyCode the key code of the key that was released
	 */
	void keyReleased(const int keyCode);

private:
	static const int* initializeKeyCodes(const int* const keyCodes);
};

} /* namespace keyboard */
} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_INPUT__KEYBOARDCONTROLKEYINPUTSOURCE_H_ */

/*
 * KeyboardControlKeyInputSource.cpp
 *
 *  Created on: 30/03/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/input/keyboard/KeyboardControlKeyInputSource.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace input {
namespace keyboard {

KeyboardControlKeyInputSource::KeyboardControlKeyInputSource(const int* const keyCodes) :
	keyCodes(initializeKeyCodes(keyCodes)) {
}

KeyboardControlKeyInputSource::~KeyboardControlKeyInputSource() {
	delete[] this->keyCodes;
}

void KeyboardControlKeyInputSource::keyPressed(const int keyCode) {
	for (int i = 0; i < ControlKeyCode::BUTTON_COUNT; ++i) {
		if (this->keyCodes[i] == keyCode) {
			setControlKeyEnabled(i, true);
		}
	}
}

void KeyboardControlKeyInputSource::keyReleased(const int keyCode) {
	for (int i = 0; i < ControlKeyCode::BUTTON_COUNT; ++i) {
		if (this->keyCodes[i] == keyCode) {
			setControlKeyEnabled(i, false);
		}
	}
}

const int* KeyboardControlKeyInputSource::initializeKeyCodes(const int* const keyCodes) {
	int* const keyCodeArray = new int[ControlKeyCode::BUTTON_COUNT];
	memcpy(keyCodeArray, keyCodes, ControlKeyCode::BUTTON_COUNT * sizeof(int));
	return keyCodeArray;
}

} /* namespace keyboard */
} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

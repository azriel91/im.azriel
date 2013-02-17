/*
 * SynchronizedControlKeyInputSource.h
 *
 *  Created on: 14/01/2013
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_INPUT__SYNCHRONIZEDCONTROLKEYINPUTSOURCE_H_
#define __IM_AZRIEL_HEROQUEST_INPUT__SYNCHRONIZEDCONTROLKEYINPUTSOURCE_H_

#include <set>

#include "im/azriel/common/imports/SdlImports.h"
#include "im/azriel/heroquest/input/ControlKeyCode.h"
#include "im/azriel/heroquest/input/ControlKeyEvent.h"
#include "im/azriel/heroquest/input/ControlKeyInputSource.h"
#include "im/azriel/heroquest/input/ControlKeyListener.h"

using namespace std;

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

/**
 * This class does not fire key events as keys are pressed or released; it fires events when the #fireEvents() function
 * is called. This allows a synchronized calling thread to determine when events are fired.
 */
class SynchronizedControlKeyInputSource: public ControlKeyInputSource {
private:
	/**
	 * Lock to prevent the control key state buffer from being read and written to simultaneously.
	 */
	SDL_mutex* const bufferLock;
	/**
	 * The state of the control keys that was used on the previous frame.
	 */
	bool* const previousControlKeysState;
	/**
	 * Buffer to track the state of the control keys on the current frame.
	 */
	bool* const currentControlKeysState;

public:
	SynchronizedControlKeyInputSource();
	virtual ~SynchronizedControlKeyInputSource();

	/**
	 * Fires #ControlKeyEvents based on the input that happened between this call and the previous call of this
	 * function.
	 */
	void fireEvents();

protected:
	/**
	 * Sets the specified control key's enabled state.
	 *
	 * @param code the control key code
	 * @param enabled the state of the control key
	 */
	void setControlKeyEnabled(const int code, const bool enabled);

private:
	/**
	 * Calculate the resultant control key presses of the current frame, and create #ControlKeyEvents for each of them.
	 * A #ControlKeyEvent is generated for a control key iff it was {@code false} in the previous state and {@code true}
	 * on the current state.
	 *
	 * @return the set of events indicating key presses
	 */
	const set<const ControlKeyEvent*>* getControlKeyPresses() const;
	/**
	 * Calculate the resultant control key releases of the current frame, and create #ControlKeyEvents for each of them.
	 * A #ControlKeyEvent is generated for a control key iff it was {@code true} in the previous state and {@code false}
	 * on the current state.
	 *
	 * @return the set of events indicating key releases
	 */
	const set<const ControlKeyEvent*>* getControlKeyReleases() const;
	/**
	 * Persists the current control key state as the previous control key state buffer.
	 */
	void persistCurrentControlKeyState();

};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_INPUT__SYNCHRONIZEDCONTROLKEYINPUTSOURCE_H_ */

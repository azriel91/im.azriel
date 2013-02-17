/*
 * ControlKeyEvent.h
 *
 *  Created on: 1/01/2013
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYEVENT_H_
#define __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYEVENT_H_

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

// forward declaration
class ControlKeyInputSource;

class ControlKeyEvent {
private:
	/**
	 * The control key code.
	 */
	const int code;
	/**
	 * The #ControlKeyInputSource that fired this event.
	 */
	const ControlKeyInputSource* const source;

public:
	ControlKeyEvent(const ControlKeyInputSource* const source, const int code);
	virtual ~ControlKeyEvent();

	/**
	 * Get the control key code.
	 *
	 * @return the control key code which must be one of the values defined in #ControlKeyCode
	 */
	const int getCode() const;
	/**
	 * Get the #ControlKeyInputSource that fired this event.
	 *
	 * @return the control key input source
	 */
	const ControlKeyInputSource* getSource() const;
};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYEVENT_H_ */

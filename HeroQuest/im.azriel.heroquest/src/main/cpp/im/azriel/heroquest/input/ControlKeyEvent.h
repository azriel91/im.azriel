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
	const int code;
	const ControlKeyInputSource* const source;

public:
	ControlKeyEvent(const ControlKeyInputSource* const source, const int code);
	virtual ~ControlKeyEvent();

	const int getCode() const;
	const ControlKeyInputSource* getSource() const;
};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYEVENT_H_ */

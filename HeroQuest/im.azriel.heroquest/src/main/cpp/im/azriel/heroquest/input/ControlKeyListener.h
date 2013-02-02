/*
 * ControlKeyListener.h
 *
 *  Created on: 1/01/2013
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYLISTENER_H_
#define __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYLISTENER_H_

#include "im/azriel/heroquest/input/ControlKeyEvent.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

class ControlKeyListener {
public:
	ControlKeyListener();
	virtual ~ControlKeyListener();

	virtual void controlKeyPressed(const ControlKeyEvent* const event) = 0;
	virtual void controlKeyReleased(const ControlKeyEvent* const event) = 0;
};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYLISTENER_H_ */

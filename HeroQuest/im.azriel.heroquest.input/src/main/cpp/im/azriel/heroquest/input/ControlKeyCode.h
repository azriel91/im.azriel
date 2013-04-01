/*
 * ControlKeyCode.h
 *
 *  Created on: 1/01/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYCODE_H_
#define __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYCODE_H_

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

class ControlKeyCode {
public:
	static constexpr int UP = 1;
	static constexpr int DOWN = UP + 1;
	static constexpr int LEFT = DOWN + 1;
	static constexpr int RIGHT = LEFT + 1;
	static constexpr int ATTACK = RIGHT + 1;
	static constexpr int JUMP = ATTACK + 1;
	static constexpr int DEFEND = JUMP + 1;

	static constexpr int BUTTON_COUNT = DEFEND + 1;
};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYCODE_H_ */

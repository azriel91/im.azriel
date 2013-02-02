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

class SynchronizedControlKeyInputSource: public ControlKeyInputSource {
private:
	SDL_mutex* const bufferLock;
	bool* const previousControlKeysState;
	bool* const currentControlKeysState;

private:
	const set<const ControlKeyEvent*>* getControlKeyPresses() const;
	const set<const ControlKeyEvent*>* getControlKeyReleases() const;
	void persistCurrentControlKeyState();

protected:
	void setControlKeyEnabled(const int code, const bool enabled);

public:
	SynchronizedControlKeyInputSource();
	virtual ~SynchronizedControlKeyInputSource();

	void fireEvents();
};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_INPUT__SYNCHRONIZEDCONTROLKEYINPUTSOURCE_H_ */

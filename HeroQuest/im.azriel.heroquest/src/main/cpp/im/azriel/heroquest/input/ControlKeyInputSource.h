/*
 * ControlKeyInputSource.h
 *
 *  Created on: 1/01/2013
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYINPUTSOURCE_H_
#define __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYINPUTSOURCE_H_

#include <set>

#include "im/azriel/common/imports/SdlImports.h"
#include "im/azriel/heroquest/input/ControlKeyListener.h"

using namespace std;

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

class ControlKeyInputSource {
	friend class SynchronizedControlKeyInputSource;
private:
	SDL_mutex* const listenerLock;
	set<ControlKeyListener*>* const listeners;

public:
	ControlKeyInputSource();
	virtual ~ControlKeyInputSource();

	void registerControlKeyListener(ControlKeyListener* const listener);
	void unregisterControlKeyListener(ControlKeyListener* const listener);

protected:
	/**
	 * @return the set of ControlKeyListeners that are registered with this input source
	 */
	const set<ControlKeyListener*> getListeners() const;
};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYINPUTSOURCE_H_ */

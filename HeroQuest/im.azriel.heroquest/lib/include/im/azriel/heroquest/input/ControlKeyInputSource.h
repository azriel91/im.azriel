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
	/**
	 * Lock to prevent listeners from being added/removed simultaneously.
	 */
	SDL_mutex* const listenerLock;
	/**
	 * The set of listeners that this input source will notify when a control key input event occurs.
	 */
	set<ControlKeyListener*>* const listeners;

public:
	ControlKeyInputSource();
	virtual ~ControlKeyInputSource();

	/**
	 * Register a #ControlKeyListener with this input source.
	 *
	 * @param listener the listener to register
	 */
	void registerControlKeyListener(ControlKeyListener* const listener);
	/**
	 * Unregister a #ControlKeyListener from this input source.
	 *
	 * @param listener the listener to unregister
	 */
	void unregisterControlKeyListener(ControlKeyListener* const listener);

protected:
	/**
	 * @return the set of ControlKeyListeners that are registered with this input source
	 */
	const set<ControlKeyListener*> getListeners() const;
	/**
	 * Sets the specified control key's enabled state.
	 *
	 * @param code the control key code
	 * @param enabled the state of the control key
	 */
	virtual void setControlKeyEnabled(const int code, const bool enabled);
};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_INPUT__CONTROLKEYINPUTSOURCE_H_ */

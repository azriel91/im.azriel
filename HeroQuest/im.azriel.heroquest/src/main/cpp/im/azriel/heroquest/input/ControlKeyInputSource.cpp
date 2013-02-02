/*
 * ControlKeyInputSource.cpp
 *
 *  Created on: 1/01/2013
 *      Author: Azriel
 */

#include "im/azriel/heroquest/input/ControlKeyInputSource.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

ControlKeyInputSource::ControlKeyInputSource() :
		listenerLock(SDL_CreateMutex()),
		listeners(new set<ControlKeyListener*>()) {
}

ControlKeyInputSource::~ControlKeyInputSource() {
	SDL_DestroyMutex(this->listenerLock);
	delete this->listeners;
}

void ControlKeyInputSource::registerControlKeyListener(ControlKeyListener* const listener) {
	SDL_mutexP(this->listenerLock);
	this->listeners->insert(listener);
	SDL_mutexV(this->listenerLock);
}

void ControlKeyInputSource::unregisterControlKeyListener(ControlKeyListener* const listener) {
	SDL_mutexP(this->listenerLock);
	this->listeners->erase(listener);
	SDL_mutexV(this->listenerLock);
}

const set<ControlKeyListener*> ControlKeyInputSource::getListeners() const {
	SDL_mutexP(this->listenerLock);
	set<ControlKeyListener*> listenersCopy(*this->listeners);
	SDL_mutexV(this->listenerLock);
	return listenersCopy;
}

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

/*
 * SynchronizedControlKeyInputSource.cpp
 *
 *  Created on: 14/01/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/input/SynchronizedControlKeyInputSource.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

SynchronizedControlKeyInputSource::SynchronizedControlKeyInputSource() :
		        bufferLock(SDL_CreateMutex()),
		        previousControlKeysState(new bool[ControlKeyCode::BUTTON_COUNT]),
		        currentControlKeysState(new bool[ControlKeyCode::BUTTON_COUNT]) {
	for (int i = 0; i < ControlKeyCode::BUTTON_COUNT; ++i) {
		this->previousControlKeysState[i] = false;
		this->currentControlKeysState[i] = false;
	}
}

SynchronizedControlKeyInputSource::~SynchronizedControlKeyInputSource() {
	SDL_DestroyMutex(this->bufferLock);
	delete[] this->previousControlKeysState;
	delete[] this->currentControlKeysState;
}

const set<const ControlKeyEvent*>* SynchronizedControlKeyInputSource::getControlKeyPresses() const {
	SDL_mutexP(this->bufferLock);
	set<const ControlKeyEvent*>* keyPressEvents = new set<const ControlKeyEvent*>();

	for (int i = 0; i < ControlKeyCode::BUTTON_COUNT; ++i) {
		if (this->currentControlKeysState[i] && !this->previousControlKeysState[i]) {
			keyPressEvents->insert(new ControlKeyEvent(this, i));
		}
	}

	SDL_mutexV(this->bufferLock);
	return keyPressEvents;
}

const set<const ControlKeyEvent*>* SynchronizedControlKeyInputSource::getControlKeyReleases() const {
	SDL_mutexP(this->bufferLock);
	set<const ControlKeyEvent*>* keyReleaseEvents = new set<const ControlKeyEvent*>();

	for (int i = 0; i < ControlKeyCode::BUTTON_COUNT; ++i) {
		if (!this->currentControlKeysState[i] && this->previousControlKeysState[i]) {
			keyReleaseEvents->insert(new ControlKeyEvent(this, i));
		}
	}

	SDL_mutexV(this->bufferLock);
	return keyReleaseEvents;
}

void SynchronizedControlKeyInputSource::persistCurrentControlKeyState() {
	SDL_mutexP(this->bufferLock);
	memcpy(this->previousControlKeysState, this->currentControlKeysState, sizeof(bool) * ControlKeyCode::BUTTON_COUNT);
	SDL_mutexV(this->bufferLock);
}

void SynchronizedControlKeyInputSource::setControlKeyEnabled(const int code, const bool enabled) {
	SDL_mutexP(this->bufferLock);
	this->currentControlKeysState[code] = enabled;
	SDL_mutexV(this->bufferLock);
}

void SynchronizedControlKeyInputSource::fireEvents() {
	SDL_mutexP(this->listenerLock);
	SDL_mutexP(this->bufferLock);

	const set<const ControlKeyEvent*>* keyPressEvents = getControlKeyPresses();
	const set<const ControlKeyEvent*>* keyReleaseEvents = getControlKeyReleases();

	// loop through each listener and fire events
	for (set<ControlKeyListener*>::iterator it = this->listeners->begin(); it != this->listeners->end(); ++it) {
		ControlKeyListener* const listener = (*it);

		for (set<const ControlKeyEvent*>::const_iterator eventIterator = keyPressEvents->begin();
		        eventIterator != keyPressEvents->end(); eventIterator++) {
			const ControlKeyEvent* const event = (*eventIterator);
			listener->controlKeyPressed(event);
		}
		for (set<const ControlKeyEvent*>::const_iterator eventIterator = keyReleaseEvents->begin();
		        eventIterator != keyReleaseEvents->end(); eventIterator++) {
			const ControlKeyEvent* const event = (*eventIterator);
			listener->controlKeyReleased(event);
		}
	}

	// delete events
	for (set<const ControlKeyEvent*>::const_iterator eventIterator = keyPressEvents->begin();
	        eventIterator != keyPressEvents->end(); eventIterator++) {
		delete (*eventIterator);
	}
	delete keyPressEvents;

	for (set<const ControlKeyEvent*>::const_iterator eventIterator = keyReleaseEvents->begin();
	        eventIterator != keyReleaseEvents->end(); eventIterator++) {
		delete (*eventIterator);
	}
	delete keyReleaseEvents;

	persistCurrentControlKeyState();

	SDL_mutexV(this->bufferLock);
	SDL_mutexV(this->listenerLock);
}

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

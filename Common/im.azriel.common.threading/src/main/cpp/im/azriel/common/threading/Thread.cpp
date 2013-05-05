/*
 * Thread.cpp
 *
 *  Created on: 3/02/2013
 *      Author: azriel
 */

#include "im/azriel/common/threading/Thread.h"

namespace im {
namespace azriel {
namespace common {
namespace threading {

Thread::Thread(Runnable* const runnable) :
		runnable(runnable), thread(nullptr) {
}

Thread::~Thread() {
}

void Thread::start() {
	this->thread = SDL_CreateThread(runThread, this);
}

const int Thread::join() {
	int exitCode = 0;
	SDL_WaitThread(thread, &exitCode);
	return exitCode;
}

int Thread::runThread(void* const thread) {
	Thread* t = reinterpret_cast<Thread*>(thread);
	return t->runnable->run();
}

} /* namespace threading */
} /* namespace common */
} /* namespace azriel */
} /* namespace im */

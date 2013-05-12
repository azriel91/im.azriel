/*
 * Thread.h
 *
 *  Created on: 3/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_COMMON_THREADING__THREAD_H_
#define __IM_AZRIEL_COMMON_THREADING__THREAD_H_

#include "im/azriel/common/imports/SdlImports.h"
#include "im/azriel/common/threading/Runnable.h"

namespace im {
namespace azriel {
namespace common {
namespace threading {

class Thread {
private:
	Runnable* const runnable;

public:
	Thread(Runnable* const runnable);
	virtual ~Thread();

	void start();
	/**
	 * Waits for this thread to terminate, and returns the exitCode provided by the argument Runnable's run() method.
	 *
	 * @return the exitCode
	 */
	const int join();

private:
	SDL_Thread* thread;

private:
	static int runThread(void* const thread);
};

} /* namespace threading */
} /* namespace common */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_COMMON_THREADING__THREAD_H_ */

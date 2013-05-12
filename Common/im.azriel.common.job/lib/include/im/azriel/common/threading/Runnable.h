/*
 * Runnable.h
 *
 *  Created on: 3/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_COMMON_THREADING__RUNNABLE_H_
#define __IM_AZRIEL_COMMON_THREADING__RUNNABLE_H_

namespace im {
namespace azriel {
namespace common {
namespace threading {

class Runnable {
public:
	Runnable();
	virtual ~Runnable();

	/**
	 * This method is called by the Thread class when it is started.
	 *
	 * @return the exit code, which is implementation specific
	 */
	virtual const int run() = 0;
};

} /* namespace threading */
} /* namespace common */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_COMMON_THREADING__RUNNABLE_H_ */

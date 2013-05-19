/*
 * LoadingActivity.h
 *
 *  Created on: 18/04/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING__LOADINGACTIVITY_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING__LOADINGACTIVITY_H_

#include "im/azriel/common/job/Job.hpp"
#include "im/azriel/heroquest/activity/Activity.h"

using namespace im::azriel::common::job;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace loading {

template<class T>
class LoadingActivity: public Activity {
private:
	Job<T>* const job;

public:
	LoadingActivity(const im::azriel::heroquest::environment::Environment* const environment,
	        const GlPainter* const painter, Job<T>* const job);
	virtual ~LoadingActivity();

	/**
	 * Function that requests this Activity to redraw itself. Should only be called by the UI thread.
	 */
	void redraw();
	/**
	 * Signals this listener that a control key has been pressed.
	 *
	 * @param event the ControlKeyEvent carrying details of the key press
	 */
	virtual void controlKeyPressed(const ControlKeyEvent* const event);
	/**
	 * Signals this listener that a control key has been released.
	 *
	 * @param event the ControlKeyEvent carrying details of the key release
	 */
	virtual void controlKeyReleased(const ControlKeyEvent* const event);

protected:
	/**
	 * The activity event loop to be implemented by subclasses.
	 */
	void activityLoop();
	/**
	 * Function called before this activity runs. This is called after initialize and after every resume.
	 */
	void preHook();
	/**
	 * Function when this activity stops running. This is called before finalize and after every stop.
	 */
	void postHook();
};

template<class T>
LoadingActivity<T>::LoadingActivity(const im::azriel::heroquest::environment::Environment* const environment,
		const GlPainter* const painter, Job<T>* const job) :
		Activity(environment, painter), job(job) {
}

template<class T>
LoadingActivity<T>::~LoadingActivity() {
}

template<class T>
void LoadingActivity<T>::redraw() {
	glClear(GL_COLOR_BUFFER_BIT);
	const string statusMessage = this->job->getStatusMessage();
	this->painter->paintString(statusMessage, 0, 0);
}

template<class T>
void LoadingActivity<T>::controlKeyPressed(const ControlKeyEvent* const event) {
}

template<class T>
void LoadingActivity<T>::controlKeyReleased(const ControlKeyEvent* const event) {
}

template<class T>
void LoadingActivity<T>::activityLoop() {
	if (this->job->isComplete()) {
		LoadingActivity<T>::endActivity(LoadingActivity<T>::ExitCode::SUCCESS);
	}
}

template<class T>
void LoadingActivity<T>::preHook() {
	if (!this->job->isComplete() && !this->job->isRunning()) {
		this->job->start();
	}
}

template<class T>
void LoadingActivity<T>::postHook() {
}

} /* namespace loading */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING__LOADINGACTIVITY_H_ */

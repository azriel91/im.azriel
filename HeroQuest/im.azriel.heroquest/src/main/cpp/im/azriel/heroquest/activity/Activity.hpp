/*
 * Activity.hpp
 *
 *  Created on: 3/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY__ACTIVITY_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY__ACTIVITY_H_

#include <cmath>
#include <typeinfo>

#include "im/azriel/common/imports/SdlImports.h"
#include "im/azriel/common/logger/Logger.h"
#include "im/azriel/common/threading/Runnable.h"
#include "im/azriel/common/threading/Thread.h"
#include "im/azriel/desktop/application/Application.h"
#include "im/azriel/desktop/graphics/painter/Painter.h"
#include "im/azriel/heroquest/environment/Environment.h"
#include "im/azriel/heroquest/input/ControlKeyListener.h"

using namespace im::azriel::common::logger;
using namespace im::azriel::common::threading;
using namespace im::azriel::desktop::application;
using namespace im::azriel::desktop::graphics::painter;
using namespace im::azriel::heroquest::environment;
using namespace im::azriel::heroquest::input;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {

template<class T = void>
class Activity: public Runnable, public ControlKeyListener {

public:
	/**
	 * Exit codes for activities.
	 */
	enum ExitCode {
		NONE, SUCCESS, STACK, FAIL
	};

	static constexpr int ENDED = 1000;

private:

	// === constants === //
	static constexpr double DEFAULT_FPS = 30.0;

private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class
	 */
	static Logger* const LOGGER;

#endif
	/**
	 * Thread that runs this activity.
	 */
	Thread* thread;
	/**
	 * Time delay between frames (in ms).
	 */
	const Uint32 delay;
	/**
	 * Lock for starting/stopping this activity
	 */
	SDL_mutex* const activityLock;

protected:
	/**
	 * The application environment.
	 */
	const im::azriel::heroquest::environment::Environment* environment;
	/**
	 * The painter instance to render images to the screen.
	 */
	const Painter* painter;
	/**
	 * Whether this activity is running.
	 */
	bool running;
	/**
	 * This activity's exit code.
	 */
	ExitCode exitCode;
	/**
	 * The activity to run on top of this activity, should this activity return with a STACK exit code.
	 */
	Activity* stackActivity;
	/**
	 * The value returned by this activity when it ends.
	 */
	T* returnValue;

public:
	Activity(const im::azriel::heroquest::environment::Environment* const environment, const Painter* const painter);
	Activity(const im::azriel::heroquest::environment::Environment* const environment, const Painter* const painter,
	        const double fps);
	virtual ~Activity();

	/**
	 * Starts this activity.
	 */
	void start();
	/**
	 * Requests this activity to end at the end of its current event loop.
	 */
	void stop();
	/**
	 * Main function call for thread.
	 */
	int run();
	/**
	 * Function that requests this Activity to redraw itself. Should only be called by the UI thread.
	 */
	virtual void redraw() = 0;
	/**
	 * Gets the exit code of this activity.
	 */
	virtual ExitCode getExitCode();
	/**
	 * Returns the stack activity if this activity ends its Task with the STACK exit code.
	 *
	 * @return the activity
	 */
	Activity<>* getStackActivity();
	/**
	 * Gets the return value of this
	 */
	virtual T* getReturnValue();

	/**
	 * Function called when this activity is first started. This runs on the main thread. Resources in this method call
	 * should be freed in the #finalize() method.
	 */
	virtual void initialize();
	/**
	 * Function called when this activity is terminated. This runs on the main thread.
	 */
	virtual void finalize();
protected:
	/**
	 * Function called before this activity runs. This is called after initialize and after every resume.
	 */
	virtual void preHook();
	/**
	 * Function when this activity stops running. This is called before finalize and after every stop.
	 */
	virtual void postHook();
	/**
	 * The activity event loop to be implemented by subclasses.
	 */
	virtual void activityLoop() = 0;

private:
	/**
	 * Pushes a VIDEO_EXPOSE SDL event requesting the screen to be redrawn.
	 */
	void requestRedraw();
};

#ifdef ENABLE_LOGGING
template<class T>
Logger* const Activity<T>::LOGGER = Logger::getLogger("Activity<T>::LOGGER");
#endif

template<class T>
Activity<T>::Activity(const im::azriel::heroquest::environment::Environment* const environment,
        const Painter* const painter) :
		        thread(nullptr),
		        delay((Uint32) (1000.0 / DEFAULT_FPS)),
		        activityLock(SDL_CreateMutex()),
		        environment(environment),
		        painter(painter),
		        running(false),
		        exitCode(NONE),
		        stackActivity(nullptr),
		        returnValue(nullptr) {

}

template<class T>
Activity<T>::Activity(const im::azriel::heroquest::environment::Environment* const environment,
        const Painter* const painter, const double fps) :
		        thread(nullptr),
		        delay((Uint32) (1000.0 / fps)),
		        activityLock(SDL_CreateMutex()),
		        environment(environment),
		        painter(painter),
		        running(false),
		        exitCode(NONE),
		        stackActivity(nullptr),
		        returnValue(nullptr) {

}

template<class T>
Activity<T>::~Activity() {
	SDL_DestroyMutex(this->activityLock);
}

template<class T>
void Activity<T>::start() {
	this->running = true;
	if (this->thread == nullptr) {
#ifdef ENABLE_LOGGING
		LOGGER->info("Starting Activity: [%s]", typeid(*this).name());
#endif
		this->thread = new Thread(this);
		this->thread->start();
	} else {
#ifdef ENABLE_LOGGING
		LOGGER->warn("Activity: [%s] started multiple times", typeid(*this).name());
#endif
	}
}

template<class T>
int Activity<T>::run() {
	this->exitCode = ExitCode::SUCCESS;

	// run prehook in main thread
	class PrehookRunner: public Runnable {
	private:
		Activity* const activity;
	public:
		PrehookRunner(Activity* activity) :
				activity(activity) {
		}
		virtual ~PrehookRunner() {
		}
		int run() {
			this->activity->preHook();
			return 0;
		}
	} prehookRunner = { this };
	Application::runInMainThread(&prehookRunner);

	// activity loop
	while (this->running) {
		Uint32 startTime = SDL_GetTicks();

		activityLoop();
		requestRedraw();

		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		SDL_Delay(max((Uint32) 0, this->delay - elapsedTime));
	}

	// run posthook in main thread
	class PosthookRunner: public Runnable {
	private:
		Activity* const activity;
	public:
		PosthookRunner(Activity* activity) :
				activity(activity) {
		}
		virtual ~PosthookRunner() {
		}
		int run() {
			this->activity->postHook();
			return 0;
		}
	} posthookRunner = { this };
	Application::runInMainThread(&posthookRunner);

	SDL_Event userEvent;
	userEvent.type = SDL_USEREVENT;
	userEvent.user.code = Activity::ENDED;
	SDL_PushEvent(&userEvent);

	return this->exitCode;
}

template<class T>
void Activity<T>::stop() {
	this->running = false;
	if (this->thread != nullptr) {
		this->thread->join();
		delete this->thread;
		this->thread = nullptr;
	}
}

template<class T>
typename Activity<T>::ExitCode Activity<T>::getExitCode() {
	return this->exitCode;
}

template<class T>
Activity<>* Activity<T>::getStackActivity() {
	return this->stackActivity;
}

template<class T>
T* Activity<T>::getReturnValue() {
	return nullptr;
}

template<class T>
void Activity<T>::initialize() {
}

template<class T>
void Activity<T>::finalize() {
}

template<class T>
void Activity<T>::preHook() {
}

template<class T>
void Activity<T>::postHook() {
}

template <class T>
void Activity<T>::requestRedraw() {
	SDL_Event event;
	event.type = SDL_VIDEOEXPOSE;
	SDL_PushEvent(&event);
}

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY__ACTIVITY_H_ */

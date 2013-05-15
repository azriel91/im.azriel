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
#include "im/azriel/desktop/graphics/gl/painter/GlPainter.h"
#include "im/azriel/heroquest/environment/Environment.h"
#include "im/azriel/heroquest/input/Controls.h"
#include "im/azriel/heroquest/input/ControlKeyListener.h"

using namespace im::azriel::common::logger;
using namespace im::azriel::common::threading;
using namespace im::azriel::desktop::application;
using namespace im::azriel::desktop::graphics::gl::painter;
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
	 * Lock for starting/stopping this activity
	 */
	SDL_mutex* const activityLock;
	/**
	 * Time delay between frames (in ms).
	 */
	const Uint32 delay;
	/**
	 * This activity's exit code.
	 */
	ExitCode exitCode;
	/**
	 * The value returned by this activity when it ends.
	 */
	T* returnValue;
	/**
	 * Thread that runs this activity.
	 */
	Thread* thread;

protected:
	/**
	 * The application environment.
	 */
	const im::azriel::heroquest::environment::Environment* environment;
	/**
	 * The painter instance to render images to the screen.
	 */
	const GlPainter* painter;
	/**
	 * Whether this activity is running.
	 */
	bool running;
	/**
	 * The activity to run on top of this activity, should this activity return with a STACK exit code.
	 */
	Activity* stackActivity;

public:
	Activity(const im::azriel::heroquest::environment::Environment* const environment, const GlPainter* const painter);
	Activity(const im::azriel::heroquest::environment::Environment* const environment, const GlPainter* const painter,
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
	const int run();
	/**
	 * Function that requests this Activity to redraw itself. Should only be called by the UI thread.
	 */
	virtual void redraw() = 0;
	/**
	 * Fires the synchronized control input sources' control key events.
	 */
	void fireSynchronizedControlKeyEvents() const;
	/**
	 * Gets the exit code of this activity.
	 *
	 * @return the exit code
	 */
	virtual ExitCode getExitCode() const;
	/**
	 * Returns the stack activity if this activity ends its Task with the STACK exit code.
	 *
	 * @return the activity
	 */
	Activity<>* getStackActivity() const;
	/**
	 * Gets the return value of this activity.
	 *
	 * @return the return value
	 */
	virtual T* getReturnValue() const;

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
	 * The activity event loop to be implemented by subclasses.
	 */
	virtual void activityLoop() = 0;
	/**
	 * Ends the current activity with the specified exit code, which must be one of:
	 * <ul>
	 * <li>ExitCode::SUCCESS</li>
	 * <li>ExitCode::STACK</li>
	 * <li>ExitCode::FAIL</li>
	 * </ul>
	 *
	 * If ExitCode::STACK is provided, then by contract the caller must have already set the value of the stackActivity.
	 *
	 * @param exitCode the exit code
	 */
	void endActivity(const ExitCode exitCode);
	/**
	 * Function called before this activity runs. This is called after initialize and after every resume.
	 */
	virtual void preHook();
	/**
	 * Function when this activity stops running. This is called before finalize and after every stop.
	 */
	virtual void postHook();
	/**
	 * Set the value returned by this activity when it ends.
	 *
	 * @param returnValue the return value
	 */
	void setReturnValue(const T* const returnValue);

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
		const GlPainter* const painter) :
				activityLock(SDL_CreateMutex()),
				delay((Uint32) (500.0 / DEFAULT_FPS)),
				exitCode(NONE),
				returnValue(nullptr),
				thread(nullptr),
				environment(environment),
				painter(painter),
				running(false),
				stackActivity(nullptr) {
}

template<class T>
Activity<T>::Activity(const im::azriel::heroquest::environment::Environment* const environment,
		const GlPainter* const painter, const double fps) :
				activityLock(SDL_CreateMutex()),
				delay((Uint32) (1000.0 / fps)),
				exitCode(NONE),
				returnValue(nullptr),
				thread(nullptr),
				environment(environment),
				painter(painter),
				running(false),
				stackActivity(nullptr) {
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
const int Activity<T>::run() {
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
		const int run() {
			this->activity->preHook();
			return 0;
		}
	} prehookRunner = { this };
	Application::runInMainThread(&prehookRunner);

	// activity loop
	while (this->running) {
		Uint32 startTime = SDL_GetTicks();

		fireSynchronizedControlKeyEvents();
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
		const int run() {
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
void Activity<T>::fireSynchronizedControlKeyEvents() const {
	const Controls* const controls = this->environment->getControls();
	auto const controlKeyInputSources = controls->getControlKeyInputSources();
	for (auto const controlKeyInputSource : *controlKeyInputSources) {
		controlKeyInputSource->fireEvents();
	}
}

template<class T>
typename Activity<T>::ExitCode Activity<T>::getExitCode() const {
	return this->exitCode;
}

template<class T>
Activity<>* Activity<T>::getStackActivity() const {
	return this->stackActivity;
}

template<class T>
T* Activity<T>::getReturnValue() const {
	return this->returnValue;
}

template<class T>
void Activity<T>::initialize() {
}

template<class T>
void Activity<T>::finalize() {
}

template<class T>
void Activity<T>::endActivity(const ExitCode exitCode) {
	this->exitCode = exitCode;
	this->running = false;
}

template<class T>
void Activity<T>::preHook() {
}

template<class T>
void Activity<T>::postHook() {
}

template<class T>
void Activity<T>::setReturnValue(const T* const returnValue) {
	this->returnValue = returnValue;
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

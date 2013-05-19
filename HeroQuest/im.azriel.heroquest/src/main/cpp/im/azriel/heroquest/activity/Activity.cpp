/*
 * Activity.cpp
 *
 *  Created on: 3/02/2013
 *      Author: azriel
 */

#include <cmath>
#include <typeinfo>

#include "im/azriel/heroquest/activity/Activity.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {

#ifdef ENABLE_LOGGING
Logger* const Activity::LOGGER = Logger::getLogger("Activity::LOGGER");
#endif

Activity::Activity(const im::azriel::heroquest::environment::Environment* const environment,
		const GlPainter* const painter) :
				activityLock(SDL_CreateMutex()),
				delay((Uint32) (500.0 / DEFAULT_FPS)),
				exitCode(NONE),
				running(false),
				stackActivity(nullptr),
				thread(nullptr),
				environment(environment),
				painter(painter) {
}

Activity::Activity(const im::azriel::heroquest::environment::Environment* const environment,
		const GlPainter* const painter, const double fps) :
				activityLock(SDL_CreateMutex()),
				delay((Uint32) (1000.0 / fps)),
				exitCode(NONE),
				running(false),
				stackActivity(nullptr),
				thread(nullptr),
				environment(environment),
				painter(painter) {
}

Activity::~Activity() {
	SDL_DestroyMutex(this->activityLock);
}

void Activity::start() {
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

const int Activity::run() {
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

void Activity::stop() {
	this->running = false;
	if (this->thread != nullptr) {
		this->thread->join();
		delete this->thread;
		this->thread = nullptr;
	}
}

void Activity::fireSynchronizedControlKeyEvents() const {
	const Controls* const controls = this->environment->getControls();
	auto const controlKeyInputSources = controls->getControlKeyInputSources();
	for (auto const controlKeyInputSource : *controlKeyInputSources) {
		controlKeyInputSource->fireEvents();
	}
}

typename Activity::ExitCode Activity::getExitCode() const {
	return this->exitCode;
}

Activity* Activity::getStackActivity() const {
	return this->stackActivity;
}

void Activity::initialize() {
}

void Activity::finalize() {
}

void Activity::endActivity(const ExitCode exitCode) {
	this->exitCode = exitCode;
	this->running = false;
}

void Activity::preHook() {
}

void Activity::postHook() {
}

void Activity::setStackActivity(Activity* const stackActivity) {
	this->stackActivity = stackActivity;
}

void Activity::requestRedraw() {
	SDL_Event event;
	event.type = SDL_VIDEOEXPOSE;
	SDL_PushEvent(&event);
}

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

/*
 * HeroQuestApplication.cpp
 *
 *  Created on: 4/11/2012
 *      Author: azriel
 */

#include "im/azriel/heroquest/HeroQuestApplication.h"

namespace im {
namespace azriel {
namespace heroquest {

#ifdef ENABLE_LOGGING
Logger* const HeroQuestApplication::LOGGER = Logger::getLogger("HeroQuestApplication::LOGGER");
#endif

HeroQuestApplication::HeroQuestApplication(const int viewportWidth, const int viewportHeight) :
		Application(viewportWidth, viewportHeight), activityStack(new stack<Activity<>*>()), currentActivity(nullptr) {

}

HeroQuestApplication::~HeroQuestApplication() {
	delete this->activityStack;
}

void HeroQuestApplication::handleActivityChange() {
	if (this->currentActivity == nullptr) {
		if (this->activityStack->empty()) {
			// TODO: exit application?
			this->currentActivity = nullptr;
		} else {
			this->currentActivity = this->activityStack->top();
			this->activityStack->pop();
//			registerListener(this->currentActivity);
			this->currentActivity->start();
		}
		return;
	}

	Activity<>::ExitCode exitCode = this->currentActivity->getExitCode();
	switch (exitCode) {
		case Activity<>::ExitCode::SUCCESS:
#ifdef ENABLE_LOGGING
			HeroQuestApplication::LOGGER->info("Activity %s returned with exit code: %d.",
			        typeid(*this->currentActivity).name(), exitCode);
#endif
			this->currentActivity->stop();
//		unregisterListener(this->currentActivity);
			this->currentActivity->finalize();
			delete this->currentActivity;

			if (this->activityStack->empty()) {
				// TODO: exit application?
				this->currentActivity = nullptr;
			} else {
				this->currentActivity = this->activityStack->top();
				this->activityStack->pop();
//			registerListener(this->currentActivity);
				this->currentActivity->start();
			}
			break;

		case Activity<>::ExitCode::FAIL:
#ifdef ENABLE_LOGGING
			HeroQuestApplication::LOGGER->error("Activity %s returned with exit code: %d.",
			        typeid(*this->currentActivity).name(), exitCode);
#endif
//		unregisterListener(this->currentActivity);
			this->currentActivity->finalize();
			delete this->currentActivity;
			if (activityStack->empty()) {
				// TODO: exit application?
				this->currentActivity = nullptr;
			} else {
				this->currentActivity = this->activityStack->top();
				this->activityStack->pop();
//			registerListener(this->currentActivity);
				this->currentActivity->start();
			}
			break;

		case Activity<>::ExitCode::STACK: {
#ifdef ENABLE_LOGGING
			HeroQuestApplication::LOGGER->info("Activity %s returned with exit code: %d.",
			        typeid(*this->currentActivity).name(), exitCode);
#endif
			this->currentActivity->stop();
//		unregisterListener(this->currentActivity);
			this->activityStack->push(this->currentActivity);
			Activity<>* stackActivity = this->currentActivity->getStackActivity();
			this->currentActivity = stackActivity;
			stackActivity->initialize();
//		registerListener(this->currentActivity);
			stackActivity->start();
		}
			break;

		default:
			break;
	}
}

void HeroQuestApplication::handleKeyDown(SDL_Event* const event) {
	switch (event->key.keysym.sym) {
		case SDLK_ESCAPE:
			quit(0);
			break;

		case SDLK_F4:
			if (event->key.keysym.mod & KMOD_ALT) {
				quit(0);
			}
			break;

		default:
			break;
	}
}

void HeroQuestApplication::handleKeyUp(SDL_Event* const event) {
	const int keyCode = event->key.keysym.sym;
	switch (keyCode) {
		case SDLK_ESCAPE:
			break;

		case SDLK_LAST:
			break;

		default:
			break;
	}
}

void HeroQuestApplication::handleMouseEvent(SDL_Event* const event) {

}

void HeroQuestApplication::handleUserEvent(SDL_Event* const event) {
	switch (event->user.code) {
		case Activity<>::ENDED:
			handleActivityChange();
			break;
	}
}

void HeroQuestApplication::redraw() {

}

} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

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
		        Application(viewportWidth, viewportHeight),
		        controls(Controls::loadFromFile("controls.xml")),
		        theme(Theme::loadFromFile("theme.xml")),
		        environment(initEnvironment(viewportWidth, viewportHeight, theme)),
		        painter(initGlPainter(theme)),
		        activityStack(new stack<Activity*>()),
		        currentActivity(new StartUpActivity(this->environment, this->painter)) {
}

HeroQuestApplication::~HeroQuestApplication() {
	delete this->activityStack;
	delete this->theme;
	delete this->environment;
	delete this->controls;
}

void HeroQuestApplication::start() {
	this->currentActivity->initialize();
	this->currentActivity->start();
}

void HeroQuestApplication::handleActivityChange() {
	if (this->currentActivity == nullptr) {
		if (this->activityStack->empty()) {
			this->currentActivity = nullptr;

			// no activities left on stack, exit the application
			quit(0);

		} else {
			this->currentActivity = this->activityStack->top();
			this->activityStack->pop();
			registerControlKeyListener(this->currentActivity);
			this->currentActivity->start();
		}
		return;
	}

	Activity::ExitCode exitCode = this->currentActivity->getExitCode();
	switch (exitCode) {
		case Activity::ExitCode::SUCCESS:
#ifdef ENABLE_LOGGING
			HeroQuestApplication::LOGGER->info("Activity %s returned with exit code: %d.",
			        typeid(*this->currentActivity).name(), exitCode);
#endif
			this->currentActivity->stop();
			unregisterControlKeyListener(this->currentActivity);
			this->currentActivity->finalize();
			delete this->currentActivity;

			if (this->activityStack->empty()) {
				this->currentActivity = nullptr;

				// no activities left on stack, exit the application
				quit(0);

			} else {
				this->currentActivity = this->activityStack->top();
				this->activityStack->pop();
				registerControlKeyListener(this->currentActivity);
				this->currentActivity->start();
			}
			break;

		case Activity::ExitCode::FAIL:
#ifdef ENABLE_LOGGING
			HeroQuestApplication::LOGGER->error("Activity %s returned with exit code: %d.",
			        typeid(*this->currentActivity).name(), exitCode);
#endif
			unregisterControlKeyListener(this->currentActivity);
			this->currentActivity->finalize();
			delete this->currentActivity;
			if (this->activityStack->empty()) {
				this->currentActivity = nullptr;

				// no activities left on stack, exit the application
				quit(0);

			} else {
				this->currentActivity = this->activityStack->top();
				this->activityStack->pop();
				registerControlKeyListener(this->currentActivity);
				this->currentActivity->start();
			}
			break;

		case Activity::ExitCode::STACK: {
#ifdef ENABLE_LOGGING
			HeroQuestApplication::LOGGER->info("Activity %s returned with exit code: %d.",
			        typeid(*this->currentActivity).name(), exitCode);
#endif
			this->currentActivity->stop();
			unregisterControlKeyListener(this->currentActivity);
			this->activityStack->push(this->currentActivity);
			Activity* stackActivity = this->currentActivity->getStackActivity();
			this->currentActivity = stackActivity;
			stackActivity->initialize();
			registerControlKeyListener(this->currentActivity);
			stackActivity->start();
		}
			break;

		default:
			break;
	}
}

void HeroQuestApplication::handleKeyDown(SDL_Event* const event) {
	const int keyCode = event->key.keysym.sym;
	switch (keyCode) {
		case SDLK_ESCAPE:
			quit(0);
			break;

		case SDLK_F4:
			if (event->key.keysym.mod & KMOD_ALT) {
				quit(0);
			}
			break;

		default:
			for (auto const keyboardControlKeyInputSource : *this->controls->getKeyboardSynchronizedControlKeyInputSources()) {
				keyboardControlKeyInputSource->keyPressed(keyCode);
			}
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
			for (auto const keyboardControlKeyInputSource : *this->controls->getKeyboardSynchronizedControlKeyInputSources()) {
				keyboardControlKeyInputSource->keyReleased(keyCode);
			}
			break;
	}
}

void HeroQuestApplication::handleMouseEvent(SDL_Event* const event) {

}

void HeroQuestApplication::handleUserEvent(SDL_Event* const event) {
	switch (event->user.code) {
		case Activity::ENDED:
			handleActivityChange();
			break;
	}
}

const im::azriel::heroquest::environment::Environment* HeroQuestApplication::initEnvironment(const int viewportWidth,
        const int viewportHeight, const Theme* const theme) const {
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
	const im::azriel::heroquest::environment::Environment* environment =
	        new im::azriel::heroquest::environment::Environment(viewportWidth, viewportHeight, videoInfo->current_w,
	                videoInfo->current_h, this->controls, theme);
	return environment;
}

void HeroQuestApplication::redraw() {
	this->currentActivity->redraw();
}

const GlPainter* HeroQuestApplication::initGlPainter(const Theme* const theme) const {
	const string textWidthString = theme->getConstant("text-width");
	const string textHeightString = theme->getConstant("text-height");
	const int textWidth = atoi(textWidthString.c_str());
	const int textHeight = atoi(textHeightString.c_str());
	return new GlPainter(theme->getConstant("text-path"), textWidth, textHeight);
}

void HeroQuestApplication::registerControlKeyListener(ControlKeyListener* const listener) const {
	for (auto const controlKeyInputSource : *this->controls->getControlKeyInputSources()) {
		controlKeyInputSource->registerControlKeyListener(listener);
	}
}

void HeroQuestApplication::unregisterControlKeyListener(ControlKeyListener* const listener) const {
	for (auto const controlKeyInputSource : *this->controls->getControlKeyInputSources()) {
		controlKeyInputSource->unregisterControlKeyListener(listener);
	}
}

} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

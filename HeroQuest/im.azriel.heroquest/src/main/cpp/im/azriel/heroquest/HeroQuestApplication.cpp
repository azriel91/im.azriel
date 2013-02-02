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
		Application(viewportWidth, viewportHeight) {

}

HeroQuestApplication::~HeroQuestApplication() {

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

}

void HeroQuestApplication::redraw() {

}

} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

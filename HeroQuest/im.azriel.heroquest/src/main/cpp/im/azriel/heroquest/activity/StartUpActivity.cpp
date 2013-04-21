/*
 * StartUpActivity.cpp
 *
 *  Created on: 9/02/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/activity/StartUpActivity.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {

StartUpActivity::StartUpActivity(const im::azriel::heroquest::environment::Environment* const environment,
		const GlPainter* const painter) :
		Activity<>(environment, painter) {
}

StartUpActivity::~StartUpActivity() {
}

void StartUpActivity::redraw() {
}

void StartUpActivity::controlKeyPressed(const ControlKeyEvent* const event) {
}

void StartUpActivity::controlKeyReleased(const ControlKeyEvent* const event) {
}

void StartUpActivity::activityLoop() {
	this->stackActivity = new MainMenuActivity(this->environment, this->painter);
	this->exitCode = ExitCode::STACK;
	this->running = false;
}

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

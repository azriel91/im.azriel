/*
 * LoadingActivity.cpp
 *
 *  Created on: 18/04/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/activity/loading/LoadingActivity.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace loading {

LoadingActivity::LoadingActivity(const im::azriel::heroquest::environment::Environment* const environment,
        const GlPainter* const painter) :
		Activity<const ApplicationConfiguration>(environment, painter), objectConfiguration(nullptr) {
}

LoadingActivity::~LoadingActivity() {
}

void LoadingActivity::redraw() {
}

void LoadingActivity::controlKeyPressed(const ControlKeyEvent* const event) {
}

void LoadingActivity::controlKeyReleased(const ControlKeyEvent* const event) {
}

const ApplicationConfiguration* LoadingActivity::getReturnValue() const {
	return this->objectConfiguration;
}

void LoadingActivity::activityLoop() {
}

} /* namespace loading */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

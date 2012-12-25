/*
 * Environment.cpp
 *
 *  Created on: 4/11/2012
 *      Author: azriel
 */

#include "Environment.h"
#include "im/azriel/desktop/application/environment/Environment.h"

namespace im {
namespace azriel {
namespace desktop {
namespace application {
namespace environment {

Environment::Environment(const int viewportWidth, const int viewportHeight, const int screenWidth,
		const int screenHeight) :
				screenWidth(screenWidth),
				screenHeight(screenHeight),
				viewportWidth(viewportWidth),
				viewportHeight(viewportHeight) {
}

Environment::~Environment() {
}

const int Environment::getScreenWidth() const {
	return this->screenWidth;
}

const int Environment::getScreenHeight() const {
	return this->screenHeight;
}

const int Environment::getViewportWidth() const {
	return this->viewportWidth;
}

const int Environment::getViewportHeight() const {
	return this->viewportHeight;
}

} /* namespace environment */
} /* namespace application */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

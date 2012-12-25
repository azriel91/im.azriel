/*
 * Environment.cpp
 *
 *  Created on: 4/11/2012
 *      Author: Azriel
 */

#include "im/azriel/heroquest/environment/Environment.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace environment {

Environment::Environment(const int viewportWidth, const int viewportHeight, const int screenWidth,
		const int screenHeight, const Theme* const theme) :
				im::azriel::desktop::application::environment::Environment(viewportWidth, viewportHeight, screenWidth,
						screenHeight),
				theme(theme) {
}

Environment::~Environment() {
}

const Theme* Environment::getTheme() const {
	return this->theme;
}

void Environment::setTheme(const Theme* const theme) {
	this->theme = theme;
}

} /* namespace environment */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

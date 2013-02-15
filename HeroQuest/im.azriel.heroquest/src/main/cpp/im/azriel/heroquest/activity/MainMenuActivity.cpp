/*
 * MainMenuActivity.cpp
 *
 *  Created on: 12/02/2013
 *      Author: azriel
 */

#include "MainMenuActivity.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {

MainMenuActivity::MainMenuActivity(const im::azriel::heroquest::environment::Environment* const environment,
        const Painter* const painter) :
		Activity<>(environment, painter), startImage(nullptr) {
}

MainMenuActivity::~MainMenuActivity() {
}

void MainMenuActivity::redraw() {
	this->painter->paint(this->startImage, 0, 0);
}

void MainMenuActivity::preHook() {
	this->startImage = GlImageFactory::loadImage(
			        this->environment->getTheme()->getPathForImage(Theme::Image::MAIN_START));
}

void MainMenuActivity::postHook() {
	delete this->startImage;
}

void MainMenuActivity::activityLoop() {

}

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

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
        const GlPainter* const painter) :
		Activity<>(environment, painter), startImage(nullptr) {
}

MainMenuActivity::~MainMenuActivity() {
}

void MainMenuActivity::redraw() {
	glClear(GL_COLOR_BUFFER_BIT);
	this->painter->paint(this->startImage, 0, 0);
}

void MainMenuActivity::controlKeyPressed(const ControlKeyEvent* const event) {
}

void MainMenuActivity::controlKeyReleased(const ControlKeyEvent* const event) {
}

void MainMenuActivity::preHook() {
	const Theme* const theme = this->environment->getTheme();
	const WidgetData* const startWidgetData = theme->getWidgetData("main/start-game");
	const Header* const header = startWidgetData->getHeader();
	auto const imageMetadatas = header->getImageMetadatas();
	this->startImage = GlImageFactory::loadImage((*imageMetadatas)[0]->getPath());
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

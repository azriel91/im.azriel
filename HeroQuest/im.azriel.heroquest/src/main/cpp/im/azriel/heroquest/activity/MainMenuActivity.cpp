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
		        Activity<>(environment, painter),
		        startMenuItem(nullptr),
		        controlSettingsMenuItem(nullptr),
		        activeMenuItem(nullptr) {
}

MainMenuActivity::~MainMenuActivity() {
}

void MainMenuActivity::redraw() {
	glClear(GL_COLOR_BUFFER_BIT);
	this->startMenuItem->redraw();
	this->controlSettingsMenuItem->redraw();
}

void MainMenuActivity::controlKeyPressed(const ControlKeyEvent* const event) {
	this->activeMenuItem->setFocused(false);
	if (this->activeMenuItem == this->startMenuItem) {
		this->activeMenuItem = this->controlSettingsMenuItem;
	} else {
		this->activeMenuItem = this->startMenuItem;
	}
	this->activeMenuItem->setFocused(true);
}

void MainMenuActivity::controlKeyReleased(const ControlKeyEvent* const event) {
}

void MainMenuActivity::preHook() {
	const Theme* const theme = this->environment->getTheme();
	const WidgetData* const startWidgetData = theme->getWidgetData("main/start-game");
	this->startMenuItem = new MenuItem(this->painter, startWidgetData);
	this->startMenuItem->setCoordinates(0, 0);
	this->startMenuItem->setFocused(true);

	const WidgetData* const controlSettingsWidgetData = theme->getWidgetData("main/control-settings");
	this->controlSettingsMenuItem = new MenuItem(this->painter, controlSettingsWidgetData);
	this->controlSettingsMenuItem->setCoordinates(200, 0);

	this->activeMenuItem = this->startMenuItem;
}

void MainMenuActivity::postHook() {
	delete this->startMenuItem;
	this->startMenuItem = nullptr;

	delete this->controlSettingsMenuItem;
	this->controlSettingsMenuItem = nullptr;
}

void MainMenuActivity::activityLoop() {
	this->startMenuItem->update();
	this->controlSettingsMenuItem->update();
}

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

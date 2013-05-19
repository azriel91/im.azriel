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

constexpr int MainMenuActivity::MENU_ITEM_HEIGHT;
constexpr int MainMenuActivity::MENU_ITEM_WIDTH;

MainMenuActivity::MainMenuActivity(const im::azriel::heroquest::environment::Environment* const environment,
        const GlPainter* const painter) :
		Activity(environment, painter), menuItems(new vector<MenuItem*>), activeMenuItemIndex(0) {
}

MainMenuActivity::~MainMenuActivity() {
	delete this->menuItems;
}

void MainMenuActivity::redraw() {
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto menuItem : *this->menuItems) {
		menuItem->redraw();
	}
}

void MainMenuActivity::controlKeyPressed(const ControlKeyEvent* const event) {
	switch (event->getCode()) {
		case ControlKeyCode::ATTACK: {
			// TODO start activity
			auto const assetConfiguration = AssetConfiguration::loadFromFile("assets/configuration.xml");
			auto const applicationLoadingJob = ApplicationConfiguration::loadApplicationConfigurationAsJob(
			        assetConfiguration);
			LoadingActivity<const ApplicationConfiguration*>* loadingActivity = new LoadingActivity<
			        const ApplicationConfiguration*>(this->environment, this->painter, applicationLoadingJob);
			setStackActivity(loadingActivity);
			endActivity(ExitCode::STACK);
		}
			break;

		case ControlKeyCode::UP:
			selectPreviousMenuItem();
			break;

		case ControlKeyCode::DOWN:
			selectNextMenuItem();
			break;

		default:
			break;
	}
}

void MainMenuActivity::controlKeyReleased(const ControlKeyEvent* const event) {
}

void MainMenuActivity::activityLoop() {
	for (auto menuItem : *this->menuItems) {
		menuItem->update();
	}
}

void MainMenuActivity::loadMenuItems(const vector<string> menuItemIds) {
	const Theme* const theme = this->environment->getTheme();

	int i = 0;
	for (auto widgetId : menuItemIds) {
		const WidgetData* const widgetData = theme->getWidgetData(widgetId);
		auto const menuItem = new MenuItem(this->painter, widgetData);
		menuItem->setCoordinates(0, 30 + i * (MENU_ITEM_HEIGHT + 10)); // 30px offset, 10px padding

		this->menuItems->push_back(menuItem);
		i++;
	}
}

void MainMenuActivity::preHook() {
	loadMenuItems( { "main/start-game", "main/control-settings" });

	auto const startMenuItem = this->menuItems->at(0);
	startMenuItem->setFocused(true);
	this->activeMenuItemIndex = 0;
}

void MainMenuActivity::postHook() {
	for (auto menuItem : *this->menuItems) {
		delete menuItem;
	}
	this->menuItems->clear();
}

void MainMenuActivity::selectNextMenuItem() {
	auto activeMenuItem = this->menuItems->at(this->activeMenuItemIndex);
	activeMenuItem->setFocused(false);

	this->activeMenuItemIndex++;
	this->activeMenuItemIndex %= this->menuItems->size();

	activeMenuItem = this->menuItems->at(this->activeMenuItemIndex);
	activeMenuItem->setFocused(true);
}

void MainMenuActivity::selectPreviousMenuItem() {
	auto activeMenuItem = this->menuItems->at(this->activeMenuItemIndex);
	activeMenuItem->setFocused(false);

	this->activeMenuItemIndex--;
	this->activeMenuItemIndex %= this->menuItems->size();

	activeMenuItem = this->menuItems->at(this->activeMenuItemIndex);
	activeMenuItem->setFocused(true);

}

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

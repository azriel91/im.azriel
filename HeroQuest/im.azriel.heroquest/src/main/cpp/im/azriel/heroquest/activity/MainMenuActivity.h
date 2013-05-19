/*
 * MainMenuActivity.h
 *
 *  Created on: 12/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY__MAINMENUACTIVITY_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY__MAINMENUACTIVITY_H_

#include <string>

#include "im/azriel/desktop/graphics/gl/image/GlImage.h"
#include "im/azriel/desktop/graphics/gl/image/GlImageFactory.h"
#include "im/azriel/desktop/graphics/gl/painter/GlPainter.h"
#include "im/azriel/desktop/graphics/gl/session/GlImageSession.h"
#include "im/azriel/desktop/theme/xml/Header.h"
#include "im/azriel/desktop/theme/xml/ImageMetadata.h"
#include "im/azriel/desktop/theme/xml/WidgetData.h"
#include "im/azriel/heroquest/activity/Activity.h"
#include "im/azriel/heroquest/activity/widget/MenuItem.h"

// --- TODO remove after testing
#include "im/azriel/heroquest/application/config/ApplicationConfiguration.h"
#include "im/azriel/heroquest/application/config/AssetConfiguration.h"
#include "im/azriel/heroquest/activity/loading/LoadingActivity.hpp"
using namespace im::azriel::heroquest::activity::loading;
using namespace im::azriel::heroquest::application::config;
// ---

using namespace std;

using namespace im::azriel::desktop::graphics::gl::image;
using namespace im::azriel::desktop::graphics::gl::painter;
using namespace im::azriel::desktop::graphics::gl::session;
using namespace im::azriel::desktop::theme::xml;
using namespace im::azriel::heroquest::activity::widget;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {

class MainMenuActivity : public Activity {
private:
	/**
	 * The height of a menu item.
	 */
	static constexpr int MENU_ITEM_HEIGHT = 50;
	/**
	 * The width of a menu item.
	 */
	static constexpr int MENU_ITEM_WIDTH = 350;

private:
	/**
	 * List of all menu items on the main menu.
	 */
	vector<MenuItem*>* const menuItems;
	/**
	 * The index of the currently selected menu item.
	 */
	int activeMenuItemIndex;

public:
	MainMenuActivity(const im::azriel::heroquest::environment::Environment* const environment,
			const GlPainter* const painter);
	virtual ~MainMenuActivity();
	/**
	 * Function that requests this Activity to redraw itself. Should only be called by the UI thread.
	 */
	void redraw();
	/**
	 * Signals this listener that a control key has been pressed.
	 *
	 * @param event the ControlKeyEvent carrying details of the key press
	 */
	virtual void controlKeyPressed(const ControlKeyEvent* const event);
	/**
	 * Signals this listener that a control key has been released.
	 *
	 * @param event the ControlKeyEvent carrying details of the key release
	 */
	virtual void controlKeyReleased(const ControlKeyEvent* const event);

protected:
	/**
	 * The activity event loop to be implemented by subclasses.
	 */
	void activityLoop();
	/**
	 * Loads the menu items from the current theme.
	 *
	 * @param menuItemIds the ids of the menu items to load
	 */
	void loadMenuItems(const vector<string> menuItemIds);
	/**
	 * Function called before this activity runs. This is called after initialize and after every resume.
	 */
	void preHook();
	/**
	 * Function when this activity stops running. This is called before finalize and after every stop.
	 */
	void postHook();
	/**
	 * Selects the next menu item.
	 */
	void selectNextMenuItem();
	/**
	 * Selects the previous menu item.
	 */
	void selectPreviousMenuItem();
};

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY__MAINMENUACTIVITY_H_ */

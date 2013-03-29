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
#include "im/azriel/heroquest/activity/Activity.hpp"
#include "im/azriel/heroquest/activity/widget/MenuItem.h"

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

class MainMenuActivity : public Activity<void> {
private:
	MenuItem* startMenuItem;
	MenuItem* controlSettingsMenuItem;

	MenuItem* activeMenuItem;

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
	 * Function called before this activity runs. This is called after initialize and after every resume.
	 */
	void preHook();
	/**
	 * Function when this activity stops running. This is called before finalize and after every stop.
	 */
	void postHook();
	/**
	 * The activity event loop to be implemented by subclasses.
	 */
	void activityLoop();
};

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY__MAINMENUACTIVITY_H_ */

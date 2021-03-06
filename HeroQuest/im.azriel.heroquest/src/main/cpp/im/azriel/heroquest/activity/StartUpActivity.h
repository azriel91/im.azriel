/*
 * StartUpActivity.h
 *
 *  Created on: 9/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY__STARTUPACTIVITY_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY__STARTUPACTIVITY_H_

#include "im/azriel/desktop/graphics/gl/painter/GlPainter.h"
#include "im/azriel/heroquest/activity/Activity.h"
#include "im/azriel/heroquest/activity/MainMenuActivity.h"
#include "im/azriel/heroquest/environment/Environment.h"
#include "im/azriel/heroquest/input/ControlKeyEvent.h"

using namespace im::azriel::desktop::graphics::gl::image;
using namespace im::azriel::desktop::graphics::gl::painter;
using namespace im::azriel::heroquest::environment;
using namespace im::azriel::heroquest::input;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {

class StartUpActivity: public Activity {

public:
	StartUpActivity(const im::azriel::heroquest::environment::Environment* const environment,
			const GlPainter* const painter);
	virtual ~StartUpActivity();

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
};

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY__STARTUPACTIVITY_H_ */

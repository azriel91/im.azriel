/*
 * MainMenuActivity.h
 *
 *  Created on: 12/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY__MAINMENUACTIVITY_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY__MAINMENUACTIVITY_H_

#include "im/azriel/desktop/graphics/gl/image/GlImage.h"
#include "im/azriel/desktop/graphics/gl/image/GlImageFactory.h"
#include "im/azriel/desktop/graphics/painter/Painter.h"
#include "im/azriel/heroquest/activity/Activity.hpp"

using namespace im::azriel::desktop::graphics::gl::image;
using namespace im::azriel::desktop::graphics::painter;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {

class MainMenuActivity : public Activity<void> {
private:
	const GlImage* startImage;

public:
	MainMenuActivity(const im::azriel::heroquest::environment::Environment* const environment,
	        const Painter* const painter);
	virtual ~MainMenuActivity();
	/**
	 * Function that requests this Activity to redraw itself. Should only be called by the UI thread.
	 */
	void redraw();

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

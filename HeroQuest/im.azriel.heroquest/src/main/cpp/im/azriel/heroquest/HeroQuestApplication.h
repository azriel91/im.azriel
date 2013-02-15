/*
 * Application.h
 *
 *  Created on: 4/11/2012
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST__APPLICATION_H_
#define __IM_AZRIEL_HEROQUEST__APPLICATION_H_

#include <stack>

#include "im/azriel/common/logger/Logger.h"
#include "im/azriel/desktop/application/Application.h"
#include "im/azriel/desktop/graphics/painter/Painter.h"
#include "im/azriel/desktop/graphics/gl/painter/GlPainter.h"
#include "im/azriel/heroquest/activity/Activity.hpp"
#include "im/azriel/heroquest/activity/StartUpActivity.h"
#include "im/azriel/heroquest/environment/Environment.h"

using namespace std;

using namespace im::azriel::common::logger;
using namespace im::azriel::desktop::application;
using namespace im::azriel::desktop::graphics::painter;
using namespace im::azriel::desktop::graphics::gl::painter;
using namespace im::azriel::heroquest::activity;
using namespace im::azriel::heroquest::environment;

namespace im {
namespace azriel {
namespace heroquest {

class HeroQuestApplication: public Application {
private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class
	 */
	static Logger* const LOGGER;
#endif

protected:
	/**
	 * The theme to use.
	 */
	const Theme* const theme;
	/**
	 * The application environment.
	 */
	const im::azriel::heroquest::environment::Environment* const environment;
	/**
	 * The painter for this application.
	 */
	const Painter* const painter;
	/**
	 * The activity stack.
	 */
	stack<Activity<>*>* const activityStack;
	/**
	 * The currently active activity.
	 */
	Activity<>* currentActivity;

public:
	/**
	 * Start the hero quest application specifying the dimensions of the viewport.
	 *
	 * @param viewportWidth the width of the application viewport
	 * @param viewportHeight the height of the application viewport
	 */
	HeroQuestApplication(const int viewportWidth, const int viewportHeight);
	virtual ~HeroQuestApplication();

	void start();

protected:
	void handleActivityChange();
	/**
	 * Hook method for subclasses to handle key down events
	 * 
	 * @param event the key down event
	 */
	virtual void handleKeyDown(SDL_Event* const event);
	/**
	 * Hook method for subclasses to handle key up events
	 * 
	 * @param event the key up event
	 */
	virtual void handleKeyUp(SDL_Event* const event);
	/**
	 * Hook method for subclasses to handle mouse events
	 * 
	 * @param event the mouse event
	 */
	virtual void handleMouseEvent(SDL_Event* const event);
	/**
	 * Hook method for subclasses to handle user events
	 * 
	 * @param event the user event
	 */
	virtual void handleUserEvent(SDL_Event* const event);
	/**
	 * Initializes the Environment object for this application.
	 *
	 * @param viewportWidth the width of the application viewport
	 * @param viewportHeight the height of the application viewport
	 * @param theme the currently active theme for this application
	 *
	 * @return the Environment object for this application
	 */
	const im::azriel::heroquest::environment::Environment* initEnvironment(const int viewportWidth,
	        const int viewportHeight, const Theme* const theme);
	/**
	 * Hook method that gets called when the screen needs to be redrawn.
	 */
	void redraw();
};

} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST__APPLICATION_H_ */

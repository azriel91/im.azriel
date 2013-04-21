/*
 * LoadingActivity.h
 *
 *  Created on: 18/04/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING__LOADINGACTIVITY_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING__LOADINGACTIVITY_H_

#include "im/azriel/heroquest/activity/Activity.hpp"
#include "im/azriel/heroquest/activity/loading/config/ApplicationConfiguration.h"

using namespace im::azriel::heroquest::activity::loading::config;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace loading {

class LoadingActivity: public Activity<const ApplicationConfiguration> {
private:
	const ApplicationConfiguration* objectConfiguration;

public:
	LoadingActivity(const im::azriel::heroquest::environment::Environment* const environment,
			const GlPainter* const painter);
	virtual ~LoadingActivity();

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
	/**
	 * Gets the loaded HeroQuestConfiguration.
	 *
	 * @return the loaded HeroQuestConfiguration
	 */
	virtual const ApplicationConfiguration* getReturnValue() const;

protected:
	/**
	 * The activity event loop to be implemented by subclasses.
	 */
	void activityLoop();
};

} /* namespace loading */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING__LOADINGACTIVITY_H_ */

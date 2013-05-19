/*
 * Activity.h
 *
 *  Created on: 3/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY__ACTIVITY_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY__ACTIVITY_H_

#include <cmath>
#include <typeinfo>

#include "im/azriel/common/imports/SdlImports.h"
#include "im/azriel/common/logger/Logger.h"
#include "im/azriel/common/threading/Runnable.h"
#include "im/azriel/common/threading/Thread.h"
#include "im/azriel/desktop/application/Application.h"
#include "im/azriel/desktop/graphics/gl/painter/GlPainter.h"
#include "im/azriel/heroquest/environment/Environment.h"
#include "im/azriel/heroquest/input/Controls.h"
#include "im/azriel/heroquest/input/ControlKeyListener.h"

using namespace im::azriel::common::logger;
using namespace im::azriel::common::threading;
using namespace im::azriel::desktop::application;
using namespace im::azriel::desktop::graphics::gl::painter;
using namespace im::azriel::heroquest::environment;
using namespace im::azriel::heroquest::input;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {

class Activity: public Runnable, public ControlKeyListener {

public:
	/**
	 * Exit codes for activities.
	 */
	enum ExitCode {
		NONE, SUCCESS, STACK, FAIL
	};

	static constexpr int ENDED = 1000;

private:

	// === constants === //
	static constexpr double DEFAULT_FPS = 30.0;

private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class
	 */
	static Logger* const LOGGER;

#endif
	/**
	 * Lock for starting/stopping this activity
	 */
	SDL_mutex* const activityLock;
	/**
	 * Time delay between frames (in ms).
	 */
	const Uint32 delay;
	/**
	 * This activity's exit code.
	 */
	ExitCode exitCode;
	/**
	 * Whether this activity is running.
	 */
	bool running;
	/**
	 * The activity to run on top of this activity, should this activity return with a STACK exit code.
	 */
	Activity* stackActivity;
	/**
	 * Thread that runs this activity.
	 */
	Thread* thread;

protected:
	/**
	 * The application environment.
	 */
	const im::azriel::heroquest::environment::Environment* environment;
	/**
	 * The painter instance to render images to the screen.
	 */
	const GlPainter* painter;

public:
	Activity(const im::azriel::heroquest::environment::Environment* const environment, const GlPainter* const painter);
	Activity(const im::azriel::heroquest::environment::Environment* const environment, const GlPainter* const painter,
			const double fps);
	virtual ~Activity();

	/**
	 * Starts this activity.
	 */
	void start();
	/**
	 * Requests this activity to end at the end of its current event loop.
	 */
	void stop();
	/**
	 * Main function call for thread.
	 */
	const int run();
	/**
	 * Function that requests this Activity to redraw itself. Should only be called by the UI thread.
	 */
	virtual void redraw() = 0;
	/**
	 * Fires the synchronized control input sources' control key events.
	 */
	void fireSynchronizedControlKeyEvents() const;
	/**
	 * Gets the exit code of this activity.
	 *
	 * @return the exit code
	 */
	virtual ExitCode getExitCode() const;
	/**
	 * Returns the stack activity if this activity ends its Task with the STACK exit code.
	 *
	 * @return the activity
	 */
	Activity* getStackActivity() const;

	/**
	 * Function called when this activity is first started. This runs on the main thread. Resources in this method call
	 * should be freed in the #finalize() method.
	 */
	virtual void initialize();
	/**
	 * Function called when this activity is terminated. This runs on the main thread.
	 */
	virtual void finalize();

protected:
	/**
	 * The activity event loop to be implemented by subclasses.
	 */
	virtual void activityLoop() = 0;
	/**
	 * Ends the current activity with the specified exit code, which must be one of:
	 * <ul>
	 * <li>ExitCode::SUCCESS</li>
	 * <li>ExitCode::STACK</li>
	 * <li>ExitCode::FAIL</li>
	 * </ul>
	 *
	 * If ExitCode::STACK is provided, then by contract the caller must have already set the value of the stackActivity.
	 *
	 * @param exitCode the exit code
	 */
	void endActivity(const ExitCode exitCode);
	/**
	 * Function called before this activity runs. This is called after initialize and after every resume.
	 */
	virtual void preHook();
	/**
	 * Function when this activity stops running. This is called before finalize and after every stop.
	 */
	virtual void postHook();
	/**
	 * Set the activity to be used as the stack activity over this activity when it ends.
	 *
	 * @param stackActivity the stack activity
	 */
	void setStackActivity(Activity* const stackActivity);

private:
	/**
	 * Pushes a VIDEO_EXPOSE SDL event requesting the screen to be redrawn.
	 */
	void requestRedraw();
};

} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY__ACTIVITY_H_ */

/*
 * Application.h
 *
 *  Created on: 4/11/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_APPLICATION__APPLICATION_H_
#define __IM_AZRIEL_DESKTOP_APPLICATION__APPLICATION_H_

#include "im/azriel/common/imports/GlImports.h"
#include "im/azriel/common/imports/SdlImports.h"
#include "im/azriel/common/logger/Logger.h"
#include "im/azriel/common/threading/Runnable.h"
#include "im/azriel/desktop/application/environment/Environment.h"

using namespace im::azriel::common::logger;
using namespace im::azriel::common::threading;
using namespace im::azriel::desktop::application::environment;

namespace im {
namespace azriel {
namespace desktop {
namespace application {

class Application {
private:
	/**
	 * Constant indicating a user event is for a synchronous callback
	 */
	static constexpr int SYNCHRONOUS_CALLBACK = 1;

	/**
	 * Condition that the calling thread waits on before returning.
	 */
	static SDL_cond* syncCallbackCondition;
	/**
	 * Lock to allow only one sync callback to run at a time.
	 */
	static SDL_mutex* syncCallbackLock;
	/**
	 * Lock between the main thread and calling thread.
	 */
	static SDL_mutex* syncCallbackRunnableLock;
	/**
	 * Shared location to return the exit code for the last sync callback.
	 */
	static int syncCallbackExitCode;

protected:
	/**
	 * Mutex for drawing.
	 */
	SDL_mutex* const drawingLock;
	/**
	 * SDL_Surface that represents the screen.
	 */
	SDL_Surface* const screen; // Declaration comes before Environment so that it is initialized first
	/**
	 * Object that carries environmental information about the running application.
	 */
	const Environment* const environment;

private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif

public:
	/**
	 * Construct a windowed application specifying the dimensions of the viewport.
	 *
	 * @param viewportWidth the width of the application viewport
	 * @param viewportHeight the height of the application viewport
	 */
	Application(const int viewportWidth, const int viewportHeight);
	/**
	 * Construct an application specifying the dimensions of the viewport, and specifying whether the application should
	 * be fullscreen.
	 *
	 * @param viewportWidth the width of the application viewport
	 * @param viewportHeight the height of the application viewport
	 * @param fullscreen whether the application should be full screen
	 */
	Application(const int viewportWidth, const int viewportHeight, const bool fullscreen);
	virtual ~Application();
	/**
	 * Enter the main application loop.
	 */
	void mainLoop();

protected:
	/**
	 * Hook method for subclasses to handle key down events
	 * 
	 * @param event the key down event
	 */
	virtual void handleKeyDown(SDL_Event* const event) = 0;
	/**
	 * Hook method for subclasses to handle key up events
	 * 
	 * @param event the key up event
	 */
	virtual void handleKeyUp(SDL_Event* const event) = 0;
	/**
	 * Hook method for subclasses to handle mouse events
	 * 
	 * @param event the mouse event
	 */
	virtual void handleMouseEvent(SDL_Event* const event) = 0;
	/**
	 * Hook method for subclasses to handle user events
	 * 
	 * @param event the user event
	 */
	virtual void handleUserEvent(SDL_Event* const event) = 0;
	/**
	 * Sets the viewport values, resets the projection and model view matrices, and clear colour for Open Gl.
	 */
	virtual void initOpenGlSettings();
	/**
	 * Initializes the Environment object for this application.
	 *
	 * @param viewportWidth the width of the application viewport
	 * @param viewportHeight the height of the application viewport
	 *
	 * @return the Environment object for this application
	 */
	virtual const Environment* initEnvironment(const int viewportWidth, const int viewportHeight);
	/**
	 * Initializes the video settings for the application and returns the SDL_Surface* representing the screen.
	 *
	 * @param viewportWidth the width of the application viewport
	 * @param viewportHeight the height of the application viewport
	 * @param fullscreen whether the application should be full screen
	 *
	 * @return the SDL_Surface representing the screen
	 */
	SDL_Surface* initVideo(const int viewportWidth, const int viewportHeight, const bool fullscreen);
	/**
	 * Hook method that gets called when the screen needs to be redrawn.
	 */
	virtual void redraw() = 0;
	/**
	 * Exits the program.
	 * 
	 * @param exitCode
	 */
	void quit(const int exitCode);

public:
	/**
	 * Runs the specified runnable in the main thread.
	 *
	 * @param runnable the runnable to run
	 *
	 * @return the exit code returned by the runnable
	 */
	static int runInMainThread(Runnable* const runnable);
};

} /* namespace application */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_DESKTOP_APPLICATION__APPLICATION_H_ */

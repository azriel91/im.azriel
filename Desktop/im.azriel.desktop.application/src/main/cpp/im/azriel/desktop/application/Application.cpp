/*
 * Application.cpp
 *
 *  Created on: 4/11/2012
 *      Author: azriel
 */

#include "im/azriel/desktop/application/Application.h"

namespace im {
namespace azriel {
namespace desktop {
namespace application {

#ifdef ENABLE_LOGGING
Logger* const Application::LOGGER = Logger::getLogger("Application::LOGGER");
#endif

SDL_cond* Application::syncCallbackCondition = SDL_CreateCond();
SDL_mutex* Application::syncCallbackLock = SDL_CreateMutex();
SDL_mutex* Application::syncCallbackRunnableLock = SDL_CreateMutex();
int Application::syncCallbackExitCode = 0;

Application::Application(const int viewportWidth, const int viewportHeight) :
				drawingLock(SDL_CreateMutex()),
				screen(initVideo(viewportWidth, viewportHeight, false)),
				environment(initEnvironment(viewportWidth, viewportHeight)) {
	initOpenGlSettings();
}

Application::Application(const int viewportWidth, const int viewportHeight, const bool fullscreen) :
				drawingLock(SDL_CreateMutex()),
				screen(initVideo(viewportWidth, viewportHeight, fullscreen)),
				environment(initEnvironment(viewportWidth, viewportHeight)) {
	initOpenGlSettings();
}

Application::~Application() {
	SDL_DestroyMutex(this->drawingLock);
	delete this->environment;
}

void Application::mainLoop() {
	bool done = false;
	SDL_Event event;

#ifdef ENABLE_LOGGING
		LOGGER->info("Entered application main loop");
#endif

	while(!done && SDL_WaitEvent(&event)!=-1){

		switch(event.type){

		case SDL_KEYDOWN:
			handleKeyDown(&event);
			break;

		case SDL_KEYUP:
			handleKeyUp(&event);
			break;

		case SDL_QUIT:
			// quit events, exit the event loop
			done = true;
			break;

		case SDL_MOUSEMOTION:
			handleMouseEvent(&event);
			break;

		case SDL_USEREVENT:
			if (event.user.code == Application::SYNCHRONOUS_CALLBACK) {

				// run the runnable since we are the main thread
				SDL_mutexP(Application::syncCallbackRunnableLock);

				Runnable* const runnable = reinterpret_cast<Runnable*>(event.user.data1);
				Application::syncCallbackExitCode = runnable->run();

				SDL_mutexV(Application::syncCallbackRunnableLock);
				SDL_CondSignal(Application::syncCallbackCondition);
			} else {
				handleUserEvent(&event);
			}
			break;

		case SDL_VIDEOEXPOSE:
			// obtain lock
			if(SDL_mutexP(this->drawingLock) == -1){
#ifdef ENABLE_LOGGING
				LOGGER->error("Unable to obtain drawing mutex lock.");
#endif
				quit(-1);
			}

			redraw();

			// release lock
			if(SDL_mutexV(this->drawingLock) == -1){
#ifdef ENABLE_LOGGING
				LOGGER->error("Unable to release drawing mutex lock.");
#endif
				quit(-1);
			}

			// swap buffers
			SDL_GL_SwapBuffers();
			break;

		default:
			break;
		}

	}

	SDL_Quit();
}

const Environment* Application::initEnvironment(const int viewportWidth, const int viewportHeight) {
	const SDL_VideoInfo* const video = SDL_GetVideoInfo();
	return new Environment(viewportWidth, viewportHeight, video->current_w, video->current_h);
}

void Application::initOpenGlSettings() {
#ifdef ENABLE_LOGGING
	LOGGER->info("Initializing OpenGL settings");
#endif
	const int viewportWidth = this->environment->getViewportWidth();
	const int viewportHeight = this->environment->getViewportHeight();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, viewportWidth, viewportHeight);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, viewportWidth, viewportHeight, 0.0, 0.0, -255.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_NOTEQUAL, 0.0f);
}

SDL_Surface* Application::initVideo(const int viewportWidth, const int viewportHeight, const bool fullscreen) {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
#ifdef ENABLE_LOGGING
		LOGGER->error("Failed to initialize video: %s", SDL_GetError());
#endif
		quit(1);
	}

	const SDL_VideoInfo* const video = SDL_GetVideoInfo();
	const int videoFlags = SDL_OPENGL |				// using OpenGl
			SDL_HWPALETTE |							// store palette in hardware
			SDL_SRCALPHA |							// enable alpha blending
			(fullscreen ? SDL_FULLSCREEN : 0) |		// fullscreen
			(video->blit_hw ? SDL_HWACCEL : 0) |	// use hardware acceleration if hardware blits available
			(video->hw_available ? SDL_HWSURFACE : SDL_SWSURFACE);

	//enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Surface* screen = SDL_SetVideoMode(viewportWidth, viewportHeight, video->vfmt->BitsPerPixel, videoFlags);
	if (!screen) {
#ifdef ENABLE_LOGGING
		LOGGER->error("Failed to set video mode: %s", SDL_GetError());
#endif
		quit(1);
	}
	return screen;
}

void Application::quit(const int exitCode) {
	SDL_Quit();
	exit(exitCode);
}

int Application::runInMainThread(Runnable* const runnable) {

	int exitCode = 0;

	// only allow one runnable to be scheduled at a time
	SDL_mutexP(syncCallbackLock);

	SDL_mutexP(syncCallbackRunnableLock);
	SDL_Event syncCallbackEvent;
	syncCallbackEvent.type = SDL_USEREVENT;
	syncCallbackEvent.user.code = Application::SYNCHRONOUS_CALLBACK;
	syncCallbackEvent.user.data1 = runnable;
	SDL_PushEvent(&syncCallbackEvent);

	// wait for the main thread to execute the runnable
	SDL_CondWait(syncCallbackCondition, syncCallbackLock);

	exitCode = syncCallbackExitCode;

	SDL_mutexV(syncCallbackRunnableLock);
	SDL_mutexV(syncCallbackLock);

	return exitCode;
}

} /* namespace application */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

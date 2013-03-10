/*
 * Environment.h
 *
 *  Created on: 4/11/2012
 *      Author: azriel
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

namespace im {
namespace azriel {
namespace desktop {
namespace application {
namespace environment {

/**
 * The Environment class contains environmental information about the running application.
 */
class Environment {
protected:
	/**
	 * Width of the screen.
	 */
	const int screenWidth;
	/**
	 * Height of the screen.
	 */
	const int screenHeight;
	/**
	 * Width of the viewport within the window bounds.
	 */
	const int viewportWidth;
	/**
	 * Height of the viewport within the window bounds.
	 */
	const int viewportHeight;
public:
	Environment(const int viewportWidth, const int viewportHeight, const int screenWidth, const int screenHeight);
	virtual ~Environment();
	/**
	 * Get the width of the screen.
	 *
	 * @return the width of the screen in pixels
	 */
	const int getScreenWidth() const;
	/**
	 * Get the height of the screen.
	 *
	 * @return the height of the screen in pixels
	 */
	const int getScreenHeight() const;
	/**
	 * Get the width of the viewport within the window bounds.
	 *
	 * @return the width of the viewport in pixels
	 */
	const int getViewportWidth() const;
	/**
	 * Get the height of the viewport within the window bounds.
	 *
	 * @return the height of the viewport in pixels
	 */
	const int getViewportHeight() const;
};

} /* namespace environment */
} /* namespace desktop */
} /* namespace common */
} /* namespace azriel */
} /* namespace im */
#endif /* ENVIRONMENT_H_ */

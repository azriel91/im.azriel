/*
 * Image.h
 *
 *  Created on: 25/11/2012
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE__IMAGE_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE__IMAGE_H_

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {

/**
 * This is meant to be an abstract class.
 */
class Image {
protected:
	/**
	 * The width of this image.
	 */
	const int width;
	/**
	 * The height of this image.
	 */
	const int height;

public:
	virtual ~Image();

	/**
	 * @return the width of this image
	 */
	const int getWidth() const;
	/**
	 * @return the height of this image
	 */
	const int getHeight() const;

protected:
	/**
	 * @param width the width of the image
	 * @param height the height of the image
	 */
	Image(const int width, const int height);

};

} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE__IMAGE_H_ */

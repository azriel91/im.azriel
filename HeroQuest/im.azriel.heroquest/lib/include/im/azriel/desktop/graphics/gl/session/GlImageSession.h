/*
 * GlImageSession.h
 *
 *  Created on: 18/03/2013
 *      Author: azriel
 */

#ifndef GLIMAGESESSION_H_
#define GLIMAGESESSION_H_

#include "im/azriel/desktop/graphics/gl/image/GlImage.h"
#include "im/azriel/desktop/graphics/gl/image/GlImageFactory.h"
#include "im/azriel/desktop/graphics/gl/image/GlImageSheet.h"
#include "im/azriel/desktop/graphics/gl/painter/GlPainter.h"
#include "im/azriel/desktop/graphics/session/ImageSession.hpp"

using namespace im::azriel::desktop::graphics::gl::image;
using namespace im::azriel::desktop::graphics::gl::painter;
using namespace im::azriel::desktop::graphics::session;

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace session {

class GlImageSession: public ImageSession<GlImage, GlImageSheet> {

public:
	GlImageSession(const GlPainter* const painter);
	virtual ~GlImageSession();

protected:
	/**
	 * Template method for subclasses to load an image.
	 *
	 * @param path the path to the image to load
	 *
	 * @throws ImageLoadException if an error occurs while loading the image
	 */
	const GlImage* doLoadImage(const string path);
	/**
	 * Template method for subclasses to load an image sheet.
	 *
	 * @param path the path to the image sheet to load
	 * @param subImageWidth the width of each sub image on the image sheet
	 * @param subImageHeight the height of each sub image on the image sheet
	 * @param rowCount the number of rows of images on the image sheet
	 * @param columnCount the number of columns of images on the image sheet
	 *
	 * @throws ImageLoadException if an error occurs while loading the image
	 */
	const GlImageSheet* doLoadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
			const int rowCount, const int columnCount) throw (ImageLoadException);
	/**
	 * Loads an image sheet into the current image session. The loaded image sheet is returned to allow the image to be
	 * used outside of this session. The image sheet should not be freed (deleted) outside of this session.
	 * This session will automatically free the image when it is deleted.
	 *
	 * @param path the path to the image sheet to load
	 * @param subImageWidth the width of each sub image on the image sheet
	 * @param subImageHeight the height of each sub image on the image sheet
	 * @param rowCount the number of rows of images on the image sheet
	 * @param columnCount the number of columns of images on the image sheet
	 * @param border the width of the border
	 *
	 * @throws ImageLoadException if an error occurs while loading the image
	 */
	const GlImageSheet* doLoadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
			const int rowCount, const int columnCount, const int border) throw (ImageLoadException);
};

} /* namespace session */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* GLIMAGESESSION_H_ */

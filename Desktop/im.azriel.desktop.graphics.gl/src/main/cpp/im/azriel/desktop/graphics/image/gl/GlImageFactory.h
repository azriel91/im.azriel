/*
 * GlImageFactory.h
 *
 *  Created on: 9/12/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGEFACTORY_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGEFACTORY_H_

#include <string>

#include "im/azriel/common/imports/GlImports.h"
#include "im/azriel/common/imports/SdlImports.h"
#include "im/azriel/common/logger/Logger.h"
#include "im/azriel/desktop/graphics/image/exception/ImageLoadException.h"
#include "im/azriel/desktop/graphics/image/gl/GlImage.h"

using namespace std;
using namespace im::azriel::common::logger;
using namespace im::azriel::desktop::graphics::image::exception;

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {
namespace gl {

class GlImageFactory {
private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif
public:
	static const GlImage* loadImage(const string path) throw(ImageLoadException);
	static const GlImageSheet* loadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
	        const int rowCount, const int columnCount) throw(ImageLoadException);

private:
	static SDL_Surface* GlImageFactory::openImage(const string path);
};

} /* namespace gl */
} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGEFACTORY_H_ */

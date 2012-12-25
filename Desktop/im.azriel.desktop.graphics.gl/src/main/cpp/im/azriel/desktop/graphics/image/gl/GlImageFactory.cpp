/*
 * GlImageFactory.cpp
 *
 *  Created on: 9/12/2012
 *      Author: Azriel
 */

#include "im/azriel/desktop/graphics/image/gl/GlImageFactory.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {
namespace gl {

static const GlImage* GlImageFactory::loadImage(const string path) throw (ImageLoadException) {
//	const GlImage* image = new GlImage(textureId, width, height, textureWidth, textureHeight);
	return nullptr;
}

static const GlImageSheet* GlImageFactory::loadImageSheet(const string path, const int subImageWidth,
        const int subImageHeight, const int rowCount, const int columnCount) throw (ImageLoadException) {
	return nullptr;
}

static SDL_Surface* GlImageFactory::openImage(const string path) {
	SDL_Surface* image = IMG_Load(path.c_str());

	if (!image) {
#ifdef ENABLE_LOGGING
		LOGGER->error("Failed to load image: %s", path.c_str());
#endif
		throw ImageLoadException("Failed to load image: " + path);
	}

	if (image->format->BitsPerPixel == 32) {
		return image;
	}

	SDL_Surface* temp;
	temp = SDL_DisplayFormatAlpha(image);
	SDL_FreeSurface(image);
	return temp;
}

} /* namespace gl */
} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

/*
 * Image.cpp
 *
 *  Created on: 25/11/2012
 *      Author: azriel
 */

#include "im/azriel/desktop/graphics/image/Image.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {

Image::Image(const int width, const int height) :
		width(width), height(height) {
}

Image::~Image() {
}

const int Image::getWidth() const {
	return this->width;
}

const int Image::getHeight() const {
	return this->height;
}

} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

/*
 * GlImage.cpp
 *
 *  Created on: 9/12/2012
 *      Author: azriel
 */

#include "im/azriel/desktop/graphics/gl/image/GlImage.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace image {

GlImage::~GlImage() {
	glDeleteTextures(1, &(this->textureId));
}

const GLuint GlImage::getTextureId() const {
	return this->textureId;
}

const int GlImage::getTextureWidth() const {
	return this->textureWidth;
}

const int GlImage::getTextureHeight() const {
	return this->textureHeight;
}

const double GlImage::getTextureCoordinateX() const {
	return this->textureCoordinateX;
}

const double GlImage::getTextureCoordinateY() const {
	return this->textureCoordinateY;
}

GlImage::GlImage(const GLuint textureId, const int width, const int height, const int textureWidth,
        const int textureHeight) :
		        Image(width, height),
		        textureId(textureId),
		        textureWidth(textureWidth),
		        textureHeight(textureHeight),
		        textureCoordinateX((double) width / textureWidth),
		        textureCoordinateY((double) height / textureHeight) {
}

} /* namespace image */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

/*
 * GlImage.h
 *
 *  Created on: 9/12/2012
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGE_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGE_H_

#include <string>

#include "im/azriel/common/imports/GlImports.h"
#include "im/azriel/desktop/graphics/image/Image.h"

using namespace std;
using namespace im::azriel::desktop::graphics::image;

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace image {

class GlImage: public Image {
	friend class GlImageFactory;

protected:
	/**
	 * The OpenGl texture id.
	 */
	const GLuint textureId;
	/**
	 * The width of the texture for this GlImage. This will be a power of two.
	 */
	const int textureWidth;
	/**
	 * The height of the texture for this GlImage. This will be a power of two.
	 */
	const int textureHeight;
	/**
	 * The x coordinate where the edge of the actual image lies on the texture.
	 */
	const double textureCoordinateX;
	/**
	 * The y coordinate where the edge of the actual image lies on the texture.
	 */
	const double textureCoordinateY;

public:
	virtual ~GlImage();
	/**
	 * Get the OpenGl texture id.
	 *
	 * @return the texture id
	 */
	const GLuint getTextureId();
	/**
	 * Get the width of the texture for this GlImage. This will be a power of two.
	 *
	 * @return the width of the texture
	 */
	const int getTextureWidth() const;
	/**
	 * Get the height of the texture for this GlImage. This will be a power of two.
	 *
	 * @return the height of the texture
	 */
	const int getTextureHeight() const;
	/**
	 * Get the x coordinate where the edge of the actual image lies on the texture.
	 *
	 * @return the x coordinate
	 */
	const double getTextureCoordinateX() const;
	/**
	 * Get the y coordinate where the edge of the actual image lies on the texture.
	 *
	 * @return the y coordinate
	 */
	const double getTextureCoordinateY() const;

protected:
	/**
	 * Construct a GlImage.
	 *
	 * @param textureId the OpenGl texture id
	 * @param width the width of the loaded image
	 * @param height the height of the loaded image
	 * @param textureWidth the width of the texture
	 * @param textureHeight the height of the texture
	 */
	GlImage(const GLuint textureId, const int width, const int height, const int textureWidth, const int textureHeight);
};

} /* namespace image */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGE_H_ */

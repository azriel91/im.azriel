/*
 * GlImageSheet.h
 *
 *  Created on: 9/12/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGESHEET_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGESHEET_H_

#include "im/azriel/desktop/graphics/image/ImageSheet.h"
#include "im/azriel/desktop/graphics/image/gl/GlImage.h"

using namespace im::azriel::desktop::graphics::image;

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {
namespace gl {

class GlImageSheet: public ImageSheet, public GlImage {
public:
	GlImageSheet(const GLuint textureId, const int width, const int height, const int textureWidth,
	        const int textureHeight, const int subImageWidth, const int subImageHeight, const int rowCount,
	        const int columnCount);
	virtual ~GlImageSheet();
};

} /* namespace gl */
} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGESHEET_H_ */

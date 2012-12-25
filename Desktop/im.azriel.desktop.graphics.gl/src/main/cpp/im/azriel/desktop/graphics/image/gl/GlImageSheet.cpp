/*
 * GlImageSheet.cpp
 *
 *  Created on: 9/12/2012
 *      Author: azriel
 */

#include "GlImageSheet.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {
namespace gl {

GlImageSheet::GlImageSheet(const GLuint textureId, const int width, const int height, const int textureWidth,
        const int textureHeight, const int subImageWidth, const int subImageHeight, const int rowCount,
        const int columnCount) :
		        ImageSheet(width, height, subImageWidth, subImageHeight, rowCount, columnCount),
		        GlImage(textureId, width, height, textureWidth, textureHeight) {
}

GlImageSheet::~GlImageSheet() {
}

} /* namespace gl */
} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

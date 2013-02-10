/*
 * GlImageSheet.h
 *
 *  Created on: 9/12/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGESHEET_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGESHEET_H_

#include <vector>

#include "im/azriel/desktop/graphics/image/ImageSheet.h"
#include "im/azriel/desktop/graphics/gl/image/GlImage.h"
#include "im/azriel/desktop/graphics/gl/image/GlVertexMap.h"

using namespace std;
using namespace im::azriel::desktop::graphics::image;

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace image {

class GlImageSheet: public ImageSheet, public GlImage {
	friend class GlImageFactory;

protected:
	const vector<const GlVertexMap*>* const vertexMaps;

public:
	virtual ~GlImageSheet();
	const GlVertexMap* operator[](const int index) const;
	const GlVertexMap* getVertexMap(const int index) const;

protected:
	GlImageSheet(const GLuint textureId, const int width, const int height, const int textureWidth,
	        const int textureHeight, const int subImageWidth, const int subImageHeight, const int rowCount,
	        const int columnCount, const vector<const GlVertexMap*>* const vertexMaps);
};

} /* namespace image */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLIMAGESHEET_H_ */

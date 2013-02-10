/*
 * GlImageSheet.cpp
 *
 *  Created on: 9/12/2012
 *      Author: azriel
 */

#include "im/azriel/desktop/graphics/gl/image/GlImageSheet.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace image {

GlImageSheet::GlImageSheet(const GLuint textureId, const int width, const int height, const int textureWidth,
        const int textureHeight, const int subImageWidth, const int subImageHeight, const int rowCount,
        const int columnCount, const vector<const GlVertexMap*>* const vertexMaps) :
		        ImageSheet(width, height, subImageWidth, subImageHeight, rowCount, columnCount),
		        GlImage(textureId, width, height, textureWidth, textureHeight),
		        vertexMaps(vertexMaps) {
}

GlImageSheet::~GlImageSheet() {
	for (vector<const GlVertexMap*>::const_iterator it = this->vertexMaps->begin(); it != this->vertexMaps->end(); ++it) {
		const GlVertexMap* const vertexMap = *it;
		delete vertexMap;
	}
	delete this->vertexMaps;
}

const GlVertexMap* GlImageSheet::operator[](const int index) const {
	return this->vertexMaps->at(index);
}

const GlVertexMap* GlImageSheet::getVertexMap(const int index) const {
	return this->vertexMaps->at(index);
}

} /* namespace image */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

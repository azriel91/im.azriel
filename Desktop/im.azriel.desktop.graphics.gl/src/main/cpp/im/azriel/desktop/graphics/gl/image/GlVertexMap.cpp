/*
 * GlVertexMap.cpp
 *
 *  Created on: 26/12/2012
 *      Author: azriel
 */

#include "im/azriel/desktop/graphics/gl/image/GlVertexMap.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace image {

GlVertexMap::GlVertexMap(const double x1, const double y1, const double x2, const double y2) :
		x1(x1), y1(y1), x2(x2), y2(y2) {
}

GlVertexMap::~GlVertexMap() {
}

const double GlVertexMap::getX1() const {
	return this->x1;
}

const double GlVertexMap::getY1() const {
	return this->y1;
}

const double GlVertexMap::getX2() const {
	return this->x2;
}

const double GlVertexMap::getY2() const {
	return this->y2;
}

} /* namespace image */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

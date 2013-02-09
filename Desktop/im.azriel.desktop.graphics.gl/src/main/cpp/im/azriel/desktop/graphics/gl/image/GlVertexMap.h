/*
 * GlVertexMap.h
 *
 *  Created on: 26/12/2012
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLVERTEXMAP_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLVERTEXMAP_H_

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace image {

class GlVertexMap {
protected:
	/**
	 * The left x coordinate.
	 */
	const double x1;
	/**
	 * The top y coordinate.
	 */
	const double y1;
	/**
	 * The right x coordinate.
	 */
	const double x2;
	/**
	 * The bottom y coordinate.
	 */
	const double y2;
public:
	/**
	 * Construct a vertex map.
	 *
	 * @param x1 the left x coordinate
	 * @param y1 the top y coordinate
	 * @param x2 the right x coordinate
	 * @param y2 the bottom y coordinate
	 */
	GlVertexMap(const double x1, const double y1, const double x2, const double y2);
	virtual ~GlVertexMap();

	/**
	 * Get the left x coordinate
	 *
	 * @return the left x coordinate
	 */
	const double getX1();
	/**
	 * Get the top y coordinate
	 *
	 * @return the top y coordinate
	 */
	const double getY1();
	/**
	 * Get the right x coordinate
	 *
	 * @return the right x coordinate
	 */
	const double getX2();
	/**
	 * Get the bottom y coordinate
	 *
	 * @return the bottom y coordinate
	 */
	const double getY2();
};

} /* namespace image */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_GL__GLVERTEXMAP_H_ */

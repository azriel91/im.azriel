/*
 * Painter.h
 *
 *  Created on: 5/11/2012
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_PAINTER__PAINTER_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_PAINTER__PAINTER_H_

#include <string>
#include <vector>

#include "im/azriel/desktop/graphics/image/Image.h"
#include "im/azriel/desktop/graphics/image/ImageSheet.h"

using namespace std;

using namespace im::azriel::desktop::graphics::image;

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace painter {

class Painter {
public:
	Painter();
	virtual ~Painter();

	/**
	 * Paint an image.
	 *
	 * @param image the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 */
	virtual void paint(Image* const image, int const x, int const y) const = 0;
	/**
	 * Paint an image.
	 *
	 * @param image the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param a the alpha value to modify the image by (0-255)
	 */
	virtual void paint(Image* const image, int const x, int const y, int const a) const = 0;
	/**
	 * Paint an image.
	 *
	 * @param image the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param a the alpha value to modify the image by (0-255)
	 * @param flipHorizontal flip the image horizontally
	 */
	virtual void paint(Image* const image, int const x, int const y, int const a, bool const flipHorizontal) const = 0;
	/**
	 * Paint an image.
	 *
	 * @param image the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param a the alpha value to modify the image by (0-255)
	 * @param flipHorizontal flip the image horizontally
	 * @param flipVertical flip the image vertically
	 */
	virtual void paint(Image* const image, int const x, int const y, int const a, bool const flipHorizontal,
	        bool const flipVertical) const = 0;
	/**
	 * Paint an image from an image sheet.
	 *
	 * @param imageSheet the image sheet from which to source the image
	 * @param n the number of the image on the image sheet to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 */
	virtual void paint(ImageSheet* const imageSheet, int const n, int const x, int const y) const = 0;
	/**
	 * Paint an image from an image sheet.
	 *
	 * @param imageSheet the image sheet from which to source the image
	 * @param n the number of the image on the image sheet to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param a the alpha value to modify the image by (0-255)
	 */
	virtual void paint(ImageSheet* const imageSheet, int const n, int const x, int const y, int const a) const = 0;
	/**
	 * Paint an image from an image sheet.
	 *
	 * @param imageSheet the image sheet from which to source the image
	 * @param n the number of the image on the image sheet to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param a the alpha value to modify the image by (0-255)
	 * @param flipHorizontal flip the image horizontally
	 */
	virtual void paint(ImageSheet* const imageSheet, int const n, int const x, int const y, int const a,
	        bool const flipHorizontal) const = 0;
	/**
	 * Paint an image from an image sheet.
	 *
	 * @param imageSheet the image sheet from which to source the image
	 * @param n the number of the image on the image sheet to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param a the alpha value to modify the image by (0-255)
	 * @param flipHorizontal flip the image horizontally
	 * @param flipVertical flip the image vertically
	 */
	virtual void paint(ImageSheet* const imageSheet, int const n, int const x, int const y, int const a,
	        bool const flipHorizontal, bool const flipVertical) const = 0;
	/**
	 * Paint a line.
	 *
	 * @param x1 the starting x coordinate of the line
	 * @param y1 the starting y coordinate of the line
	 * @param x2 the ending x coordinate of the line
	 * @param y2 the ending y coordinate of the line
	 * @param r the value for the red component of the colour (0-255)
	 * @param g the value for the green component of the colour (0-255)
	 * @param b the value for the blue component of the colour (0-255)
	 */
	virtual void paintLine(int const x1, int const y1, int const x2, int const y2, int const r, int const g,
	        int const b) const = 0;
	/**
	 * Paint a line.
	 *
	 * @param x1 the starting x coordinate of the line
	 * @param y1 the starting y coordinate of the line
	 * @param x2 the ending x coordinate of the line
	 * @param y2 the ending y coordinate of the line
	 * @param r the value for the red component of the colour (0-255)
	 * @param g the value for the green component of the colour (0-255)
	 * @param b the value for the blue component of the colour (0-255)
	 * @param a the value for the alpha component of the colour (0-255)
	 */
	virtual void paintLine(int const x1, int const y1, int const x2, int const y2, int const r, int const g,
	        int const b, int const a) const = 0;
	/**
	 * Paint a rectangle.
	 *
	 * @param x the starting x coordinate of the rectangle
	 * @param y the starting y coordinate of the rectangle
	 * @param w the width of the rectangle
	 * @param h the height of the rectangle
	 * @param r the value for the red component of the colour (0-255)
	 * @param g the value for the green component of the colour (0-255)
	 * @param b the value for the blue component of the colour (0-255)
	 */
	virtual void paintRect(int const x, int const y, int const w, int const h, int const r, int const g,
	        int const b) const = 0;
	/**
	 * Paint a rectangle.
	 *
	 * @param x the starting x coordinate of the rectangle
	 * @param y the starting y coordinate of the rectangle
	 * @param w the width of the rectangle
	 * @param h the height of the rectangle
	 * @param r the value for the red component of the colour (0-255)
	 * @param g the value for the green component of the colour (0-255)
	 * @param b the value for the blue component of the colour (0-255)
	 * @param a the value for the alpha component of the colour (0-255)
	 */
	virtual void paintRect(int const x, int const y, int const w, int const h, int const r, int const g, int const b,
	        int const a) const = 0;
	/**
	 * Paint a string.
	 *
	 * @param x the starting x coordinate of the string
	 * @param y the starting y coordinate of the string
	 * @param r the value for the red component of the colour (0-255)
	 * @param g the value for the green component of the colour (0-255)
	 * @param b the value for the blue component of the colour (0-255)
	 */
	virtual void paintString(char* const s, double const x, double const y) const = 0;
	/**
	 * Paint a string.
	 *
	 * @param x the starting x coordinate of the string
	 * @param y the starting y coordinate of the string
	 * @param r the value for the red component of the colour (0-255)
	 * @param g the value for the green component of the colour (0-255)
	 * @param b the value for the blue component of the colour (0-255)
	 * @param a the value for the alpha component of the colour (0-255)
	 */
	virtual void paintString(char* const s, double const x, double const y, int const a) const = 0;
	/**
	 * Translate all future operations by the specified coordinates.
	 *
	 * @param x the number of units to translate future operations by along the x axis
	 * @param y the number of units to translate future operations by along the y axis
	 */
	virtual void translate(int const x, int const y) const = 0;
};

} /* namespace painter */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_PAINTER__PAINTER_H_ */

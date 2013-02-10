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
	virtual void paint(const Image* const image, const int x, const int y) const = 0;
	/**
	 * Paint an image.
	 *
	 * @param image the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param r the red value to modify the image by (0-255)
	 * @param g the green value to modify the image by (0-255)
	 * @param b the blue value to modify the image by (0-255)
	 * @param a the alpha value to modify the image by (0-255)
	 */
	virtual void paint(const Image* const image, const int x, const int y, const int r, const int g, const int b,
	        const int a) const = 0;
	/**
	 * Paint an image.
	 *
	 * @param image the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param flipHorizontal flip the image horizontally
	 * @param flipVertical flip the image vertically
	 */
	virtual void paint(const Image* const image, const int x, const int y, const bool flipHorizontal,
	        const bool flipVertical) const = 0;
	/**
	 * Paint an image.
	 *
	 * @param image the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param r the red value to modify the image by (0-255)
	 * @param g the green value to modify the image by (0-255)
	 * @param b the blue value to modify the image by (0-255)
	 * @param a the alpha value to modify the image by (0-255)
	 * @param flipHorizontal flip the image horizontally
	 * @param flipVertical flip the image vertically
	 */
	virtual void paint(const Image* const image, const int x, const int y, const int r, const int g, const int b,
	        const int a, const bool flipHorizontal, const bool flipVertical) const = 0;
	/**
	 * Paint an image from an image sheet.
	 *
	 * @param imageSheet the image sheet from which to source the image
	 * @param n the number of the image on the image sheet to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 */
	virtual void paint(const ImageSheet* const imageSheet, const int n, const int x, const int y) const = 0;
	/**
	 * Paint an image from an image sheet.
	 *
	 * @param imageSheet the image sheet from which to source the image
	 * @param n the number of the image on the image sheet to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param r the red value to modify the image by (0-255)
	 * @param g the green value to modify the image by (0-255)
	 * @param b the blue value to modify the image by (0-255)
	 * @param a the alpha value to modify the image by (0-255)
	 */
	virtual void paint(const ImageSheet* const imageSheet, const int n, const int x, const int y, const int r,
	        const int g, const int b, const int a) const = 0;
	/**
	 * Paint an image from an image sheet.
	 *
	 * @param imageSheet the image sheet from which to source the image
	 * @param n the number of the image on the image sheet to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param flipHorizontal flip the image horizontally
	 * @param flipVertical flip the image vertically
	 */
	virtual void paint(const ImageSheet* const imageSheet, const int n, const int x, const int y,
	        const bool flipHorizontal, const bool flipVertical) const = 0;
	/**
	 * Paint an image from an image sheet.
	 *
	 * @param imageSheet the image sheet from which to source the image
	 * @param n the number of the image on the image sheet to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param r the red value to modify the image by (0-255)
	 * @param g the green value to modify the image by (0-255)
	 * @param b the blue value to modify the image by (0-255)
	 * @param a the alpha value to modify the image by (0-255)
	 * @param flipHorizontal flip the image horizontally
	 * @param flipVertical flip the image vertically
	 */
	virtual void paint(const ImageSheet* const imageSheet, const int n, const int x, const int y, const int r,
	        const int g, const int b, const int a, const bool flipHorizontal, const bool flipVertical) const = 0;
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
	virtual void paintLine(const int x1, const int y1, const int x2, const int y2, const int r, const int g,
	        const int b) const = 0;
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
	virtual void paintLine(const int x1, const int y1, const int x2, const int y2, const int r, const int g,
	        const int b, const int a) const = 0;
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
	virtual void paintRect(const int x, const int y, const int w, const int h, const int r, const int g,
	        const int b) const = 0;
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
	virtual void paintRect(const int x, const int y, const int w, const int h, const int r, const int g, const int b,
	        const int a) const = 0;
	/**
	 * Paint a string.
	 *
	 * @param s the string to paint
	 * @param x the starting x coordinate of the string
	 * @param y the starting y coordinate of the string
	 * @param r the value for the red component of the colour (0-255)
	 * @param g the value for the green component of the colour (0-255)
	 * @param b the value for the blue component of the colour (0-255)
	 */
	virtual void paintString(const string s, const int x, const int y) const = 0;
	/**
	 * Paint a string, blending it with the specified colour.
	 *
	 * @param s the string to paint
	 * @param y the starting y coordinate of the string
	 * @param r the value for the red component of the colour (0-255)
	 * @param g the value for the green component of the colour (0-255)
	 * @param b the value for the blue component of the colour (0-255)
	 * @param a the value for the alpha component of the colour (0-255)
	 */
	virtual void paintString(const string s, const int x, const int y, const int r, const int g, const int b,
	        const int a) const = 0;
	/**
	 * Translate all future operations by the specified coordinates.
	 *
	 * @param x the number of units to translate future operations by along the x axis
	 * @param y the number of units to translate future operations by along the y axis
	 */
	virtual void translate(const int x, const int y) const = 0;
};

} /* namespace painter */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_PAINTER__PAINTER_H_ */

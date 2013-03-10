/*
 * GlPainter.h
 *
 *  Created on: 9/02/2013
 *      Author: azriel
 */

#ifndef GLPAINTER_H_
#define GLPAINTER_H_

#include <string>

#include "im/azriel/desktop/graphics/painter/Painter.hpp"
#include "im/azriel/desktop/graphics/gl/image/GlImage.h"
#include "im/azriel/desktop/graphics/gl/image/GlImageFactory.h"
#include "im/azriel/desktop/graphics/gl/image/GlImageSheet.h"

using namespace std;
using namespace im::azriel::desktop::graphics::gl::image;
using namespace im::azriel::desktop::graphics::painter;

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace painter {

class GlPainter: public Painter<GlImage, GlImageSheet> {
protected:
	const GlImageSheet* const textImageSheet;

public:
	GlPainter(const string textImageSheetPath, const int charWidth, const int charHeight);
	virtual ~GlPainter();

	/**
	 * Paint an image.
	 *
	 * @param image the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 */
	virtual void paint(const GlImage* const image, const int x, const int y) const;
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
	virtual void paint(const GlImage* const image, const int x, const int y, const int r, const int g, const int b,
	        const int a) const;
	/**
	 * Paint an image.
	 *
	 * @param image the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param flipHorizontal flip the image horizontally
	 * @param flipVertical flip the image vertically
	 */
	virtual void paint(const GlImage* const image, const int x, const int y, const bool flipHorizontal,
	        const bool flipVertical) const;
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
	virtual void paint(const GlImage* const image, const int x, const int y, const int r, const int g, const int b,
	        const int a, const bool flipHorizontal, const bool flipVertical) const;
	/**
	 * Paint an image from an image sheet.
	 *
	 * @param imageSheet the image sheet from which to source the image
	 * @param n the number of the image on the image sheet to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 */
	virtual void paint(const GlImageSheet* const imageSheet, const int n, const int x, const int y) const;
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
	virtual void paint(const GlImageSheet* const imageSheet, const int n, const int x, const int y, const int r,
	        const int g, const int b, const int a) const;
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
	virtual void paint(const GlImageSheet* const imageSheet, const int n, const int x, const int y,
	        const bool flipHorizontal, const bool flipVertical) const;
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
	virtual void paint(const GlImageSheet* const imageSheet, const int n, const int x, const int y, const int r,
	        const int g, const int b, const int a, const bool flipHorizontal, const bool flipVertical) const;
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
	        const int b) const;
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
	        const int b, const int a) const;
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
	        const int b) const;
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
	        const int a) const;
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
	virtual void paintString(const string s, const int x, const int y) const;
	/**
	 * Paint a string, blending it with the specified colour.
	 *
	 * @param s the string to paint
	 * @param x the starting x coordinate of the string
	 * @param y the starting y coordinate of the string
	 * @param r the value for the red component of the colour (0-255)
	 * @param g the value for the green component of the colour (0-255)
	 * @param b the value for the blue component of the colour (0-255)
	 * @param a the value for the alpha component of the colour (0-255)
	 */
	virtual void paintString(const string s, const int x, const int y, const int r, const int g, const int b,
	        const int a) const;
	/**
	 * Translate all future operations by the specified coordinates.
	 *
	 * @param x the number of units to translate future operations by along the x axis
	 * @param y the number of units to translate future operations by along the y axis
	 */
	virtual void translate(const int x, const int y) const;

protected:

	/**
	 * Paint a texture at the specified coordinates.
	 *
	 * @param textureId the texture id
	 * @param x1 the starting x coordinate of where the texture should be drawn
	 * @param y1 the starting y coordinate of where the texture should be drawn
	 * @param x2 the ending x coordinate of where the texture should be drawn
	 * @param y2 the ending y coordinate of where the texture should be drawn
	 * @param tx1 the starting texture x coordinate
	 * @param ty1 the starting texture y coordinate
	 * @param tx2 the ending texture x coordinate
	 * @param ty2 the ending texture y coordinate
	 */
	void internalPaintImage(const GLuint textureId, const int x1, const int y1, const int x2, const int y2,
	        const double tx1, const double ty1, const double tx2, const double ty2) const;
	/**
	 * Paint a texture at the specified coordinates.
	 *
	 * @param textureId the texture id
	 * @param x1 the starting x coordinate of where the texture should be drawn
	 * @param y1 the starting y coordinate of where the texture should be drawn
	 * @param x2 the ending x coordinate of where the texture should be drawn
	 * @param y2 the ending y coordinate of where the texture should be drawn
	 * @param tx1 the starting texture x coordinate
	 * @param ty1 the starting texture y coordinate
	 * @param tx2 the ending texture x coordinate
	 * @param ty2 the ending texture y coordinate
	 * @param r the alpha value to modify the image by (0-255)
	 * @param g the alpha value to modify the image by (0-255)
	 * @param b the alpha value to modify the image by (0-255)
	 * @param a the alpha value to modify the image by (0-255)
	 */
	void internalPaintImage(const GLuint textureId, const int x1, const int y1, const int x2, const int y2,
	        const double tx1, const double ty1, const double tx2, const double ty2, const int r, const int g,
	        const int b, const int a) const;
	/**
	 * Paint a string at the specified location, using the images on the passed in image sheet.
	 *
	 * @param textImageSheet the image sheet from which to source the text image
	 * @param s the string to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param r the red value to modify the image by (0-255)
	 * @param g the green value to modify the image by (0-255)
	 * @param b the blue value to modify the image by (0-255)
	 * @param a the alpha value to modify the image by (0-255)
	 */
	void internalPaintString(const GlImageSheet* const textImageSheet, const string s, const int x, const int y,
	        const int r, const int g, const int b, const int a) const;
	/**
	 * Generates an array of int coordinates such that coordinates[0~3] correspond to the following positions if not
	 * flipped:
	 * <pre>
	 * x, y		x+w, y
	 *
	 * x, y+h	x+w, y+h
	 * </pre>
	 * The caller is responsible for freeing memory with a <code>delete[] array</code> call.
	 *
	 * @return the generated array
	 */
	static const int* generateCoordinates(const int x, const int y, const int w, const int h, const bool flipHorizontal,
	        const bool flipVertical);
};

} /* namespace painter */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* GLPAINTER_H_ */

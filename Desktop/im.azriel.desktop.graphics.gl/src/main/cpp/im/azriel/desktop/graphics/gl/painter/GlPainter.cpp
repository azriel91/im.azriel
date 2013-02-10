/*
 * GlPainter.cpp
 *
 *  Created on: 9/02/2013
 *      Author: azriel
 */

#include "im/azriel/desktop/graphics/gl/painter/GlPainter.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace painter {

GlPainter::GlPainter(const string textImageSheetPath, const int charWidth, const int charHeight) :
		textImageSheet(GlImageFactory::loadImageSheet(textImageSheetPath, charWidth, charHeight, 25, 10)) {
}

GlPainter::~GlPainter() {
	delete this->textImageSheet;
}

void GlPainter::paint(const GlImage* const image, const int x, const int y) const {
	paint(image, x, y, 255, 255, 255, 255, false, false);
}

void GlPainter::paint(const GlImage* const image, const int x, const int y, const int r, const int g, const int b,
        const int a) const {
	paint(image, x, y, r, g, b, a, false, false);
}

void GlPainter::paint(const GlImage* const image, const int x, const int y, const bool flipHorizontal,
        const bool flipVertical) const {
	paint(image, x, y, 255, 255, 255, 255, flipHorizontal, flipVertical);
}

void GlPainter::paint(const GlImage* const image, const int x, const int y, const int r, const int g, const int b,
        const int a, const bool flipHorizontal, const bool flipVertical) const {
	const int* coordinates = generateCoordinates(x, y, image->getTextureWidth(), image->getTextureHeight(),
	        flipHorizontal, flipVertical);

	internalPaintImage(image->getTextureId(), coordinates[0], coordinates[1], coordinates[2], coordinates[3], 0.0, 0.0,
	        image->getTextureCoordinateX(), image->getTextureCoordinateY(), r, g, b, a);

	delete[] coordinates;
}

void GlPainter::paint(const GlImageSheet* const imageSheet, const int n, const int x, const int y) const {
	paint((GlImageSheet*) imageSheet, x, y, 255, 255, 255, 255, false, false);
}

void GlPainter::paint(const GlImageSheet* const imageSheet, const int n, const int x, const int y, const int r,
        const int g, const int b, const int a) const {
	paint((GlImageSheet*) imageSheet, x, y, r, g, b, a, false, false);
}

void GlPainter::paint(const GlImageSheet* const imageSheet, const int n, const int x, const int y,
        const bool flipHorizontal, const bool flipVertical) const {
	paint((GlImageSheet*) imageSheet, x, y, 255, 255, 255, 255, flipHorizontal, flipVertical);
}

void GlPainter::paint(const GlImageSheet* const imageSheet, const int n, const int x, const int y, const int r,
        const int g, const int b, const int a, const bool flipHorizontal, const bool flipVertical) const {

	const int* coordinates = generateCoordinates(x, y, imageSheet->getSubImageWidth(), imageSheet->getSubImageHeight(),
	        flipHorizontal, flipVertical);

	const GlVertexMap* const vertexMap = (*imageSheet)[n];
	internalPaintImage(imageSheet->getTextureId(), coordinates[0], coordinates[1], coordinates[2], coordinates[3],
	        vertexMap->getX1(), vertexMap->getY1(), vertexMap->getX2(), vertexMap->getY2(), r, g, b, a);

	delete[] coordinates;
}

void GlPainter::paintLine(const int x1, const int y1, const int x2, const int y2, const int r, const int g,
        const int b) const {
	paintLine(x1, y1, x2, y2, r, g, b, 255);
}

void GlPainter::paintLine(const int x1, const int y1, const int x2, const int y2, const int r, const int g, const int b,
        const int a) const {
	glColor4ub((GLubyte) r, (GLubyte) g, (GLubyte) b, (GLubyte) a);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

void GlPainter::paintRect(const int x, const int y, const int w, const int h, const int r, const int g,
        const int b) const {
	paintRect(x, y, w, h, r, g, b, 255);
}

void GlPainter::paintRect(const int x, const int y, const int w, const int h, const int r, const int g, const int b,
        const int a) const {
	glColor4ub((GLubyte) r, (GLubyte) g, (GLubyte) b, (GLubyte) a);
	glRecti(x, y, x + w, y + h);
}

void GlPainter::paintString(const string s, const int x, const int y) const {
	paintString(s, x, y, 255, 255, 255, 255);
}

void GlPainter::paintString(const string s, const int x, const int y, const int r, const int g, const int b,
        const int a) const {
	internalPaintString(this->textImageSheet, s, x, y, r, g, b, a);
}

void GlPainter::translate(const int x, const int y) const {
	glTranslated((GLdouble) x, (GLdouble) y, 0);
}

void GlPainter::internalPaintImage(const GLuint textureId, const int x1, const int y1, const int x2, const int y2,
        const double tx1, const double ty1, const double tx2, const double ty2) const {
	internalPaintImage(textureId, x1, y1, x2, y2, tx1, ty1, tx2, ty2, 255, 255, 255, 255);
}

void GlPainter::internalPaintImage(const GLuint textureId, const int x1, const int y1, const int x2, const int y2,
        const double tx1, const double ty1, const double tx2, const double ty2, const int r, const int g, const int b,
        const int a) const {
	glColor4b((GLubyte) r, (GLubyte) g, (GLubyte) b, (GLubyte) a);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);

	// GL_COMBINE	- multiplies rgba from the texture with glColor
	// GL_BLEND		- uses rgb from colour, a from texture
	// GL_REPLACE	- uses rgba from the texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

	glBegin(GL_QUADS);

	glTexCoord2d(tx1, ty1);
	glVertex2i(x1, y1);

	glTexCoord2d(tx1, ty2);
	glVertex2i(x1, y2);

	glTexCoord2d(tx2, ty2);
	glVertex2i(x2, y2);

	glTexCoord2d(tx2, ty1);
	glVertex2i(x2, y1);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void GlPainter::internalPaintString(const GlImageSheet* const textImageSheet, const string s, const int x, const int y,
		const int r, const int g, const int b, const int a) const {
	const int strLength = s.length();
	int xs = x;
	int ys = y;

	const int charWidth = textImageSheet->getSubImageWidth();
	const int charHeight = textImageSheet->getSubImageHeight();

	for (int i = 0; i < strLength; i++) {
		while (s[i] != '\n' && i < strLength) {
			int charImageIndex = s[i] - ' '; // offset for blank characters
			charImageIndex = max(0, charImageIndex);
			paint((GlImageSheet*) textImageSheet, charImageIndex, xs, y, r, g, b, a);
			xs += charWidth;
			i++;
		}
		xs = x;
		ys += charHeight;
	}
}

const int* GlPainter::generateCoordinates(const int x, const int y, const int w, const int h, const bool flipHorizontal,
        const bool flipVertical) {
	int* const coordinates = new int[4];
	if (flipHorizontal) {
		coordinates[0] = x + w;
		coordinates[2] = x;
	} else {
		coordinates[0] = x;
		coordinates[2] = x + w;
	}

	if (flipVertical) {
		coordinates[1] = y + h;
		coordinates[3] = y;
	} else {
		coordinates[1] = y;
		coordinates[3] = y + h;
	}

	return coordinates;
}

} /* namespace painter */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

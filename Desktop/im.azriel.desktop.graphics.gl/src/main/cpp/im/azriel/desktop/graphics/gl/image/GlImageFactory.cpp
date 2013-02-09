/*
 * GlImageFactory.cpp
 *
 *  Created on: 9/12/2012
 *      Author: Azriel
 */

#include "im/azriel/desktop/graphics/gl/image/GlImageFactory.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace image {

#ifdef ENABLE_LOGGING
Logger* const GlImageFactory::LOGGER = Logger::getLogger("GlImageFactory::LOGGER");
#endif

const GlImage* GlImageFactory::loadImage(const string path) throw (ImageLoadException) {
#ifdef ENABLE_LOGGING
	LOGGER->debug("Loading image: %s", path.c_str());
#endif
	SDL_Surface* const image = openImage(path);
	SDL_Surface* const resizedImage = convertDimensionsToPowerOfTwo(image);

	// create texture from image
	const GLuint textureId = createTexture(resizedImage);
	const GlImage* const glImage = new GlImage(textureId, image->w, image->h, resizedImage->w, resizedImage->h);

	SDL_FreeSurface(image);
	SDL_FreeSurface(resizedImage);
	return glImage;
}

const GlImageSheet* GlImageFactory::loadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
        const int rowCount, const int columnCount) throw (ImageLoadException) {
	return loadImageSheet(path, subImageWidth, subImageHeight, rowCount, columnCount, 0);
}

const GlImageSheet* GlImageFactory::loadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
        const int rowCount, const int columnCount, const int border) throw (ImageLoadException) {
#ifdef ENABLE_LOGGING
	LOGGER->debug("Loading imagesheet: %s", path.c_str());
#endif
	SDL_Surface* const image = openImage(path);
	SDL_Surface* const resizedImage = convertDimensionsToPowerOfTwo(image);

	// create texture from image
	const GLuint textureId = createTexture(resizedImage);

	// calculate vertex maps
	const vector<const GlVertexMap*>* const vertexMaps = calculateVertexMaps(subImageWidth, subImageHeight,
	        rowCount, columnCount, resizedImage->w, resizedImage->h, border);

	const GlImageSheet* const glImageSheet = new GlImageSheet(textureId, image->w, image->h, resizedImage->w,
	        resizedImage->h, subImageWidth, subImageHeight, rowCount, columnCount, vertexMaps);

	SDL_FreeSurface(image);
	SDL_FreeSurface(resizedImage);
	return glImageSheet;
}

SDL_Surface* GlImageFactory::openImage(const string path) {
	SDL_Surface* const image = IMG_Load(path.c_str());

	if (!image) {
#ifdef ENABLE_LOGGING
		LOGGER->error("Failed to load image: %s", path.c_str());
#endif
		throw ImageLoadException(string("Failed to load image: " + path).c_str());
	}

	if (image->format->BitsPerPixel == 32) {
		return image;
	}

	SDL_Surface* const temp = SDL_DisplayFormatAlpha(image);
	SDL_FreeSurface(image);
	return temp;
}

SDL_Surface* GlImageFactory::convertDimensionsToPowerOfTwo(const SDL_Surface* const image) {
	const SDL_PixelFormat* const format = image->format;
	const int width = pow(2, ceil(log2(image->w)));
	const int height = pow(2, ceil(log2(image->h)));
	SDL_Surface* const resizedImage = SDL_CreateRGBSurface(image->flags, width, height, format->BitsPerPixel,
	        format->Rmask, format->Gmask, format->Bmask, format->Amask);

	// cannot use blit because we're using openGl, so have to manually copy pixel data
	const Uint32* const srcPixels = (Uint32*) image->pixels;
	Uint32* const destPixels = (Uint32*) resizedImage->pixels;
	for (int y = 0; y < image->h; ++y) {

		const int srcOffset = y * image->w;
		const int destOffset = y * width;

		for (int x = 0; x < image->w; ++x) {
			destPixels[destOffset + x] = srcPixels[srcOffset + x];
		}
	}

	return resizedImage;
}

const GLuint GlImageFactory::createTexture(const SDL_Surface* const sSheet) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	const int length = sSheet->w * sSheet->h;
	const int bitsPerPx = sSheet->format->BitsPerPixel;
	const SDL_PixelFormat* const fmt = sSheet->format;

	GLubyte* texels = nullptr;
	switch (bitsPerPx) {
		case 8: {
			const Uint8* const source8 = static_cast<Uint8*>(sSheet->pixels);
			texels = create8BitTexMap(source8, fmt, length);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sSheet->w, sSheet->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texels);
		}
			break;

		case 32: {
			const Uint32* const source32 = static_cast<Uint32*>(sSheet->pixels);
			texels = create32BitTexMap(source32, fmt, length);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sSheet->w, sSheet->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texels);
		}
			break;
	}

	if (texels != nullptr) {
		delete texels;
	}

	return texture;
}

/*
 * TODO: check if this works (not sure if color == fmt->colorKey is correct)
 */
GLubyte* GlImageFactory::create8BitTexMap(const Uint8* const pixels, const SDL_PixelFormat* const fmt,
        const int length) {

	const int bppShift = 2; // 4 bytes per pixel, log[base 2](4) = 2
	GLubyte* const texels = new GLubyte[length * 4]; // 4 bytes per pixel
	const SDL_Color* color;

	for (int i = 0; i < length; ++i) {

		// Extract color components from a 8-bit color value
		color = &(fmt->palette->colors[pixels[i]]);

		const int offset = i << bppShift;
		texels[offset] = (GLubyte) color->r;
		texels[offset + 1] = (GLubyte) color->g;
		texels[offset + 2] = (GLubyte) color->b;
		texels[offset + 3] = (GLubyte) (((Uint32) color) == fmt->colorkey ? 0 : 255);
	}

	return texels;
}

GLubyte* GlImageFactory::create32BitTexMap(const Uint32* const pixels, const SDL_PixelFormat* const fmt,
        const int length) {

	const int bytesPerPx = 4;
	const int bppShift = 2; // 4 bytes per pixel, log[base 2](4) = 2
	const int size = length * bytesPerPx;
	GLubyte* const texels = new GLubyte[size];

	for (int i = 0; i < length; ++i) {
		/* Extracting color components from a 32-bit color value */
		Uint32 temp;
		Uint8 red, green, blue, alpha;

		/* Get Red component */
		temp = pixels[i] & fmt->Rmask; /* Isolate red component */
		temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Rloss; /* Expand to a full 8-bit number */
		red = (Uint8) temp;

		/* Get Green component */
		temp = pixels[i] & fmt->Gmask; /* Isolate green component */
		temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Gloss; /* Expand to a full 8-bit number */
		green = (Uint8) temp;

		/* Get Blue component */
		temp = pixels[i] & fmt->Bmask; /* Isolate blue component */
		temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Bloss; /* Expand to a full 8-bit number */
		blue = (Uint8) temp;

		/* Get Alpha component */
		temp = pixels[i] & fmt->Amask; /* Isolate alpha component */
		temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
		temp = temp << fmt->Aloss; /* Expand to a full 8-bit number */
		alpha = (Uint8) temp;

		const int offset = i << bppShift;
		texels[offset] = (GLubyte) red;
		texels[offset + 1] = (GLubyte) green;
		texels[offset + 2] = (GLubyte) blue;
		texels[offset + 3] = (GLubyte) alpha;
	}

	return texels;
}

const vector<const GlVertexMap*>* GlImageFactory::calculateVertexMaps(const int subImageWidth, const int subImageHeight,
        const int rowCount, const int columnCount, const int textureWidth, const int textureHeight, const int border) {

	vector<const GlVertexMap*>* const vertexMaps = new vector<const GlVertexMap*>();

	//generate texture coordinates here
	for (int i = 0; i < columnCount; ++i) {
		for (int j = 0; j < rowCount; ++j) {

			double x1 = j * (subImageWidth + border) / textureWidth;
			double y1 = i * (subImageHeight + border) / textureHeight;
			double x2 = ((j + 1.0) * (subImageWidth + border) - border) / textureWidth;
			double y2 = ((i + 1.0) * (subImageHeight + border) - border) / textureHeight;

			vertexMaps->push_back(new GlVertexMap(x1, y1, x2, y2));
		}
	} //end for each image

	return vertexMaps;
}

} /* namespace image */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

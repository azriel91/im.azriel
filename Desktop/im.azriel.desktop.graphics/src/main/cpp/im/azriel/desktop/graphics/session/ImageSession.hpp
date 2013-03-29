/**
 * ImageSession.h
 *
 *  Created on: 10/03/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_SESSION__IMAGESESSION_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_SESSION__IMAGESESSION_H_

#include <string>
#include <vector>

#include "im/azriel/desktop/graphics/painter/Painter.hpp"
#include "im/azriel/desktop/graphics/image/exception/ImageLoadException.h"

using namespace std;

using namespace im::azriel::desktop::graphics::painter;
using namespace im::azriel::desktop::graphics::image::exception;

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace session {

template<class Image, class ImageSheet, class ImageReference = void>
class ImageSession {
protected:

	class Entry {
	private:
		/**
		 * The number that the first image in this entry corresponds to in this session.
		 */
		const int offset;
		/**
		 * The image or imageSheet depending on whether this record is for a single image or an image sheet
		 */
		const ImageReference* const image;
		/**
		 * Number of images that this record contains.
		 */
		const int imageCount;
		/**
		 * Whether or not this record is for an image sheet.
		 */
		const bool imageSheet;
		/**
		 * Whether this is an entry corresponding to an externally loaded image.
		 */
		const bool external;

	public:
		/**
		 * Creates an entry for an image.
		 *
		 * @param image the image to create an entry for
		 * @param offset the number of images registered in this session prior to this entry
		 * @param external whether or not the image in this entry is loaded externally
		 */
		Entry(const ImageReference* const image, const int offset, const bool external = false);
		/**
		 * Creates an entry for an image sheet.
		 *
		 * @param imageSheet the image sheet to create an entry for
		 * @param offset the number of images registered in this session prior to this entry
		 * @param imageCount the number of sub images in the image sheet
		 * @param external whether or not the image sheet in this entry is loaded externally
		 */
		Entry(const ImageReference* const imageSheet, const int offset, const int imageCount, const bool external =
				false);
		virtual ~Entry();
		/**
		 * Get the number that the first image in this entry corresponds to in this session.
		 *
		 * @return the offset
		 */
		const int getOffset() const;
		/**
		 * Get the image or imageSheet depending on whether this record is for a single image or an image sheet
		 *
		 * @return the image for this entry
		 */
		const ImageReference* getImage() const;
		/**
		 * Get number of images that this record contains.
		 *
		 * @return the number of images
		 */
		const int getImageCount() const;
		/**
		 * Get whether or not this record is for an image sheet.
		 *
		 * @return {@code true} if it is, {@code false} otherwise
		 */
		const bool isImageSheet() const;
		/**
		 * Get whether this is an entry corresponding to an externally loaded image.
		 *
		 * @return {@code true} if it is, {@code false} otherwise
		 */
		const bool isExternal() const;
	};

protected:
	const Painter<Image, ImageSheet>* const painter;
	/**
	 * The value to use to offset the next loaded/registered image.
	 */
	int nextOffset;
	/**
	 * The images and image sheets associated with this image session.
	 */
	vector<const Entry*>* const entries;

public:
	ImageSession(const Painter<Image, ImageSheet>* const painter);
	virtual ~ImageSession();
	/**
	 * Loads an image into the current image session. The loaded image is returned to allow the image to be used outside
	 * of this session. The image should not be freed (deleted) outside of this session.
	 * This session will automatically free the image when it is deleted.
	 *
	 * @param path the path to the image to load
	 *
	 * @throws ImageLoadException if an error occurs while loading the image
	 */
	const Image* loadImage(const string path) throw (ImageLoadException);
	/**
	 * Loads an image sheet into the current image session. The loaded image sheet is returned to allow the image to be
	 * used outside of this session. The image sheet should not be freed (deleted) outside of this session.
	 * This session will automatically free the image when it is deleted.
	 *
	 * This is equivalent to calling #loadImageSheet(path, subImageWidth, subImageHeight, rowCount, columnCount, 0)
	 *
	 * @param path the path to the image sheet to load
	 * @param subImageWidth the width of each sub image on the image sheet
	 * @param subImageHeight the height of each sub image on the image sheet
	 * @param rowCount the number of rows of images on the image sheet
	 * @param columnCount the number of columns of images on the image sheet
	 *
	 * @throws ImageLoadException if an error occurs while loading the image
	 */
	const ImageSheet* loadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
			const int rowCount, const int columnCount) throw (ImageLoadException);
	/**
	 * Loads an image sheet into the current image session. The loaded image sheet is returned to allow the image to be
	 * used outside of this session. The image sheet should not be freed (deleted) outside of this session.
	 * This session will automatically free the image when it is deleted.
	 *
	 * @param path the path to the image sheet to load
	 * @param subImageWidth the width of each sub image on the image sheet
	 * @param subImageHeight the height of each sub image on the image sheet
	 * @param rowCount the number of rows of images on the image sheet
	 * @param columnCount the number of columns of images on the image sheet
	 * @param border the width of the border
	 *
	 * @throws ImageLoadException if an error occurs while loading the image
	 */
	const ImageSheet* loadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
			const int rowCount, const int columnCount, const int border) throw (ImageLoadException);
	/**
	 * Paint an image.
	 *
	 * @param imageNumber the ordinal of the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 */
	void paint(const int imageNumber, const int x, const int y) const;
	/**
	 * Paint an image.
	 *
	 * @param imageNumber the ordinal of the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param r the red value to modify the image by (0-255)
	 * @param g the green value to modify the image by (0-255)
	 * @param b the blue value to modify the image by (0-255)
	 * @param a the alpha value to modify the image by (0-255)
	 */
	void paint(const int imageNumber, const int x, const int y, const int r, const int g, const int b,
			const int a) const;
	/**
	 * Paint an image.
	 *
	 * @param imageNumber the ordinal of the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param flipHorizontal flip the image horizontally
	 * @param flipVertical flip the image vertically
	 */
	void paint(const int imageNumber, const int x, const int y, const bool flipHorizontal,
			const bool flipVertical) const;
	/**
	 * Paint an image.
	 *
	 * @param imageNumber the ordinal of the image to paint
	 * @param x the x coordinate to paint the image
	 * @param y the y coordinate to paint the image
	 * @param r the red value to modify the image by (0-255)
	 * @param g the green value to modify the image by (0-255)
	 * @param b the blue value to modify the image by (0-255)
	 * @param a the alpha value to modify the image by (0-255)
	 * @param flipHorizontal flip the image horizontally
	 * @param flipVertical flip the image vertically
	 */
	void paint(const int imageNumber, const int x, const int y, const int r, const int g, const int b,
			const int a, const bool flipHorizontal, const bool flipVertical) const;
	/**
	 * Register an externally loaded image with this image session.
	 * The caller has the responsibility of freeing the image.
	 *
	 * @param image the image to register with this session
	 */
	void registerImage(const Image* const image);
	/**
	 * Register an externally loaded image sheet with this image session.
	 * The caller has the responsibility of freeing the image sheet.
	 *
	 * @param imageSheet the image sheet to register with this session
	 * @param imageCount the number of sub images in the image sheet
	 */
	void registerImageSheet(const ImageSheet* const imageSheet, int imageCount);

protected:
	const Entry* resolveEntry(const int imageNumber) const;
	/**
	 * Template method for subclasses to load an image.
	 *
	 * @param path the path to the image to load
	 *
	 * @throws ImageLoadException if an error occurs while loading the image
	 */
	virtual const Image* doLoadImage(const string path) = 0;
	/**
	 * Template method for subclasses to load an image sheet.
	 *
	 * @param path the path to the image sheet to load
	 * @param subImageWidth the width of each sub image on the image sheet
	 * @param subImageHeight the height of each sub image on the image sheet
	 * @param rowCount the number of rows of images on the image sheet
	 * @param columnCount the number of columns of images on the image sheet
	 *
	 * @throws ImageLoadException if an error occurs while loading the image
	 */
	virtual const ImageSheet* doLoadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
			const int rowCount, const int columnCount) throw (ImageLoadException) = 0;
	/**
	 * Loads an image sheet into the current image session. The loaded image sheet is returned to allow the image to be
	 * used outside of this session. The image sheet should not be freed (deleted) outside of this session.
	 * This session will automatically free the image when it is deleted.
	 *
	 * @param path the path to the image sheet to load
	 * @param subImageWidth the width of each sub image on the image sheet
	 * @param subImageHeight the height of each sub image on the image sheet
	 * @param rowCount the number of rows of images on the image sheet
	 * @param columnCount the number of columns of images on the image sheet
	 * @param border the width of the border
	 *
	 * @throws ImageLoadException if an error occurs while loading the image
	 */
	virtual const ImageSheet* doLoadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
			const int rowCount, const int columnCount, const int border) throw (ImageLoadException) = 0;

private:
	/**
	 * Register an entry for the specified image into this session.
	 *
	 * @param image the image to register an entry for
	 * @param external (default: false) whether or not the image is externally loaded
	 */
	void registerEntryForImage(const Image* const image, const bool external = false);
	/**
	 * Register an entry for the specified image sheet into this session.
	 *
	 * @param imageSheet the image sheet to register an entry for
	 * @param external (default: false) whether or not the image sheet is externally loaded
	 */
	void registerEntryForImageSheet(const ImageSheet* const imageSheet, const int imageCount, const bool external =
			false);
};

template<class Image, class ImageSheet, class ImageReference>
ImageSession<Image, ImageSheet, ImageReference>::ImageSession(const Painter<Image, ImageSheet>* const painter) :
		painter(painter), nextOffset(0), entries(new vector<const Entry*>()) {
}

template<class Image, class ImageSheet, class ImageReference>
ImageSession<Image, ImageSheet, ImageReference>::~ImageSession() {
	for (typename vector<const Entry*>::const_iterator it = this->entries->begin(); it != this->entries->end();
				it++) {
		auto const entry = (*it);
		delete entry;
	}
	delete this->entries;
}

template<class Image, class ImageSheet, class ImageReference>
const Image* ImageSession<Image, ImageSheet, ImageReference>::loadImage(const string path) throw (ImageLoadException) {
	auto const image = doLoadImage(path);
	registerEntryForImage(image);
	return image;
}

template<class Image, class ImageSheet, class ImageReference>
const ImageSheet* ImageSession<Image, ImageSheet, ImageReference>::loadImageSheet(const string path, const int subImageWidth,
		const int subImageHeight, const int rowCount, const int columnCount) throw (ImageLoadException) {
	const int imageCount = rowCount * columnCount;
	auto const imageSheet = doLoadImageSheet(path, subImageWidth, subImageHeight, rowCount, columnCount);
	registerEntryForImageSheet(imageSheet, imageCount);
	return imageSheet;
}

template<class Image, class ImageSheet, class ImageReference>
const ImageSheet* ImageSession<Image, ImageSheet, ImageReference>::loadImageSheet(const string path, const int subImageWidth,
		const int subImageHeight, const int rowCount, const int columnCount, const int border)
				throw (ImageLoadException) {
	const int imageCount = rowCount * columnCount;
	auto const imageSheet = doLoadImageSheet(path, subImageWidth, subImageHeight, rowCount, columnCount, border);
	registerEntryForImageSheet(imageSheet, imageCount);
	return imageSheet;
}

template<class Image, class ImageSheet, class ImageReference>
void ImageSession<Image, ImageSheet, ImageReference>::registerImage(const Image* const image) {
	registerEntryForImage(image, true);
}

template<class Image, class ImageSheet, class ImageReference>
void ImageSession<Image, ImageSheet, ImageReference>::registerImageSheet(const ImageSheet* const imageSheet, int imageCount) {
	registerEntryForImageSheet(imageSheet, imageCount, true);
}

template<class Image, class ImageSheet, class ImageReference>
void ImageSession<Image, ImageSheet, ImageReference>::registerEntryForImage(const Image* const image, const bool external) {
	auto const entry = new Entry(image, this->nextOffset, external);
	this->nextOffset++;
	this->entries->push_back(entry);
}

template<class Image, class ImageSheet, class ImageReference>
void ImageSession<Image, ImageSheet, ImageReference>::registerEntryForImageSheet(const ImageSheet* const imageSheet,
		const int imageCount, const bool external) {
	auto const entry = new Entry(imageSheet, this->nextOffset, imageCount, external);
	this->nextOffset += imageCount;
	this->entries->push_back(entry);
}

template<class Image, class ImageSheet, class ImageReference>
const typename ImageSession<Image, ImageSheet, ImageReference>::Entry* ImageSession<Image, ImageSheet, ImageReference>::resolveEntry(int imageNumber) const {
	if (imageNumber < 0) {
		return nullptr;
	}

	for (typename vector<const Entry*>::const_iterator it = this->entries->begin(); it != this->entries->end();
			it++) {
		const Entry* entry = (*it);

		int offset = entry->getOffset();
		int imageCount = entry->getImageCount();

		if (imageNumber >= offset + imageCount) {
			continue;
		}
		return entry;
	}
	return nullptr;
}

template<class Image, class ImageSheet, class ImageReference>
void ImageSession<Image, ImageSheet, ImageReference>::paint(const int imageNumber, const int x, const int y) const {
	auto const entry = resolveEntry(imageNumber);
	if (entry == nullptr) {
		return;
	}

	if (entry->isImageSheet()) {
		this->painter->paint((ImageSheet*) entry->getImage(), imageNumber - entry->getOffset(), x, y);
	} else {
		this->painter->paint((Image*) entry->getImage(), x, y);
	}
}

template<class Image, class ImageSheet, class ImageReference>
void ImageSession<Image, ImageSheet, ImageReference>::paint(const int imageNumber, const int x, const int y, const int r, const int g, const int b, const int a) const {
	auto const entry = resolveEntry(imageNumber);
	if (entry == nullptr) {
		return;
	}

	if (entry->isImageSheet()) {
		this->painter->paint((ImageSheet*) entry->getImage(), imageNumber - entry->getOffset(), x, y, r, g, b, a);
	} else {
		this->painter->paint((Image*) entry->getImage(), x, y, r, g, b, a);
	}
}

template<class Image, class ImageSheet, class ImageReference>
void ImageSession<Image, ImageSheet, ImageReference>::paint(const int imageNumber, const int x, const int y, const bool flipHorizontal, const bool flipVertical) const {
	auto const entry = resolveEntry(imageNumber);
	if (entry == nullptr) {
		return;
	}

	if (entry->isImageSheet()) {
		this->painter->paint((ImageSheet*) entry->getImage(), imageNumber - entry->getOffset(), x, y, flipHorizontal, flipVertical);
	} else {
		this->painter->paint((Image*) entry->getImage(), x, y, flipHorizontal, flipVertical);
	}
}

template<class Image, class ImageSheet, class ImageReference>
void ImageSession<Image, ImageSheet, ImageReference>::paint(const int imageNumber, const int x, const int y, const int r, const int g, const int b, const int a, const bool flipHorizontal, const bool flipVertical) const {
	auto const entry = resolveEntry(imageNumber);
	if (entry == nullptr) {
		return;
	}

	if (entry->isImageSheet()) {
		this->painter->paint((ImageSheet*) entry->getImage(), imageNumber - entry->getOffset(), x, y, r, g, b, a, flipHorizontal, flipVertical);
	} else {
		this->painter->paint((Image*) entry->getImage(), x, y, r, g, b, a, flipHorizontal, flipVertical);
	}
}

template<class Image, class ImageSheet, class ImageReference>
ImageSession<Image, ImageSheet, ImageReference>::Entry::Entry(const ImageReference* const image, const int offset,
		const bool external) :
		offset(offset), image(image), imageCount(1), imageSheet(false), external(external) {
}

template<class Image, class ImageSheet, class ImageReference>
ImageSession<Image, ImageSheet, ImageReference>::Entry::Entry(const ImageReference* const imageSheet, const int offset,
		const int imageCount, const bool external) :
		offset(offset), image(imageSheet), imageCount(imageCount), imageSheet(true), external(external) {

}

template<class Image, class ImageSheet, class ImageReference>
ImageSession<Image, ImageSheet, ImageReference>::Entry::~Entry() {
}

template<class Image, class ImageSheet, class ImageReference>
const int ImageSession<Image, ImageSheet, ImageReference>::Entry::getOffset() const {
	return this->offset;
}

template<class Image, class ImageSheet, class ImageReference>
const ImageReference* ImageSession<Image, ImageSheet, ImageReference>::Entry::getImage() const {
	return this->image;
}

template<class Image, class ImageSheet, class ImageReference>
const int ImageSession<Image, ImageSheet, ImageReference>::Entry::getImageCount() const {
	return this->imageCount;
}

template<class Image, class ImageSheet, class ImageReference>
const bool ImageSession<Image, ImageSheet, ImageReference>::Entry::isImageSheet() const {
	return this->imageSheet;
}

template<class Image, class ImageSheet, class ImageReference>
const bool ImageSession<Image, ImageSheet, ImageReference>::Entry::isExternal() const {
	return this->external;
}

} /* namespace session */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_SESSION__IMAGESESSION_H_ */

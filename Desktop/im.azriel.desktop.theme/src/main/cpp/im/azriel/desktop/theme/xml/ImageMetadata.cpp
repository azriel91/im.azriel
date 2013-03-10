/*
 * ImageMetadata.cpp
 *
 *  Created on: 22/02/2013
 *      Author: azriel
 */

#include "ImageMetadata.h"

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

ImageMetadata::ImageMetadata(const string path) :
		path(path), subImageWidth(0), subImageHeight(0), rowCount(0), columnCount(0), imageSheet(false) {
}

ImageMetadata::ImageMetadata(const string path, const int subImageWidth, const int subImageHeight, const int rowCount,
        const int columnCount) :
		        path(path),
		        subImageWidth(subImageWidth),
		        subImageHeight(subImageHeight),
		        rowCount(rowCount),
		        columnCount(columnCount),
		        imageSheet(true) {
}

ImageMetadata::~ImageMetadata() {
}

const string ImageMetadata::getPath() const {
	return this->path;
}

const int ImageMetadata::getSubImageHeight() const {
	return this->subImageHeight;
}

const int ImageMetadata::getSubImageWidth() const {
	return this->subImageWidth;
}

const int ImageMetadata::getRowCount() const {
	return this->rowCount;
}

const int ImageMetadata::getColumnCount() const {
	return this->columnCount;
}

const bool ImageMetadata::isImageSheet() const {
	return this->imageSheet;
}

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

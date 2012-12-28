/*
 * ImageSheet.cpp
 *
 *  Created on: 25/11/2012
 *      Author: azriel
 */

#include "im/azriel/desktop/graphics/image/ImageSheet.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {

ImageSheet::ImageSheet(const int width, const int height, const int subImageWidth, const int subImageHeight,
		const int rowCount, const int columnCount) :
				Image(width, height),
				border(0),
				columnCount(columnCount),
				rowCount(rowCount),
				subImageHeight(subImageHeight),
				subImageWidth(subImageWidth) {
}

ImageSheet::ImageSheet(const int width, const int height, const int subImageWidth, const int subImageHeight,
		const int rowCount, const int columnCount, const int border) :
				Image(width, height),
				border(border),
				columnCount(columnCount),
				rowCount(rowCount),
				subImageHeight(subImageHeight),
				subImageWidth(subImageWidth) {
}

ImageSheet::~ImageSheet() {
}

const int ImageSheet::getBorder() const {
	return this->border;
}

const int ImageSheet::getSubImageWidth() const {
	return this->subImageWidth;
}

const int ImageSheet::getSubImageHeight() const {
	return this->subImageHeight;
}

const int ImageSheet::getRowCount() const {
	return this->rowCount;
}

const int ImageSheet::getColumnCount() const {
	return this->columnCount;
}

} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

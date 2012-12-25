/*
 * ImageSheet.h
 *
 *  Created on: 25/11/2012
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE__IMAGESHEET_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE__IMAGESHEET_H_

#include "im/azriel/desktop/graphics/image/Image.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {

class ImageSheet: public Image {
protected:
	/**
	 * The width of each individual sub-image in this image sheet.
	 */
	const int subImageWidth;
	/**
	 * The height of each individual sub-image in this image sheet.
	 */
	const int subImageHeight;
	/**
	 * The number of rows of sub-images in this image sheet.
	 */
	const int rowCount;
	/**
	 * The number of columns of sub-images in this image sheet.
	 */
	const int columnCount;

public:
	virtual ~ImageSheet();

	/**
	 * Get the width of each individual sub-image in this image sheet.
	 *
	 * @return the width of a sub-image in pixels
	 */
	const int getSubImageWidth() const;
	/**
	 * Get the height of each individual sub-image in this image sheet.
	 *
	 * @return the height of a sub-image in pixels
	 */
	const int getSubImageHeight() const;
	/**
	 * Get the number of rows of sub-images in this image sheet.
	 *
	 * @return the number of rows
	 */
	const int getRowCount() const;
	/**
	 * Get the number of columns of sub-images in this image sheet.
	 *
	 * @return the number of columns
	 */
	const int getColumnCount() const;

protected:
	/**
	 * @param width the width of the entire image sheet
	 * @param height the height of the entire image sheet
	 * @param subImageWidth the width of each sub-image in the image sheet
	 * @param subImageHeight the height of each sub-image in the image sheet
	 * @param rowCount the number of rows of sub-images in the image sheet.
	 * @param columnCount the number of columns of sub-images in the image sheet.
	 */
	ImageSheet(const int width, const int height, const int subImageWidth, const int subImageHeight, const int rowCount,
			const int columnCount);
};

} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE__IMAGESHEET_H_ */

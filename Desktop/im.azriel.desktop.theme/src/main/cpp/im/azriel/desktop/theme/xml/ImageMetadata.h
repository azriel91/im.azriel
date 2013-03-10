/*
 * ImageMetadata.h
 *
 *  Created on: 22/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_THEME_XML__IMAGEMETADATA_H_
#define __IM_AZRIEL_DESKTOP_THEME_XML__IMAGEMETADATA_H_

#include <string>

using namespace std;

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

class ImageMetadata {
private:
	const string path;
	const int subImageWidth;
	const int subImageHeight;
	const int rowCount;
	const int columnCount;
	const bool imageSheet;

public:
	ImageMetadata(const string path);
	ImageMetadata(const string path, const int subImageWidth, const int subImageHeight, const int rowCount,
	        const int columnCount);
	virtual ~ImageMetadata();
	const string getPath() const;
	const int getSubImageWidth() const;
	const int getSubImageHeight() const;
	const int getRowCount() const;
	const int getColumnCount() const;
	const bool isImageSheet() const;
};

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_THEME_XML__IMAGEMETADATA_H_ */

/*
 * Header.h
 *
 *  Created on: 22/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_THEME_XML__HEADER_H_
#define __IM_AZRIEL_DESKTOP_THEME_XML__HEADER_H_

#include <vector>

#include "im/azriel/desktop/theme/xml/ImageMetadata.h"

using namespace std;

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

class Header {
private:
	/**
	 * The metadatas for images and image sheets.
	 */
	const vector<const ImageMetadata*>* const imageMetadatas;

public:
	Header(const vector<const ImageMetadata*>* const imageMetadatas);
	virtual ~Header();
	/**
	 * Get the metadatas for images and image sheets.
	 *
	 * @return the vector of metadata
	 */
	const vector<const ImageMetadata*>* getImageMetadatas() const;
};

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_THEME_XML__HEADER_H_ */

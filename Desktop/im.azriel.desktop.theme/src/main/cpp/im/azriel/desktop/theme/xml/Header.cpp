/*
 * Header.cpp
 *
 *  Created on: 22/02/2013
 *      Author: azriel
 */

#include "Header.h"

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

Header::Header(const vector<const ImageMetadata*>* const imageMetadatas) :
		imageMetadatas(imageMetadatas) {
}

Header::~Header() {
	for (vector<const ImageMetadata*>::const_iterator it = this->imageMetadatas->begin(); it != this->imageMetadatas->end(); it++) {
		const ImageMetadata* imageMetadata = (*it);
		delete imageMetadata;
	}
	delete this->imageMetadatas;
}

const vector<const ImageMetadata*>* const Header::getImageMetadatas() const {
	return this->imageMetadatas;
}

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

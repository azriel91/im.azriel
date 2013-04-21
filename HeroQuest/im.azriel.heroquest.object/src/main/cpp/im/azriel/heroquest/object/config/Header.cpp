/*
 * Header.cpp
 *
 *  Created on: 22/02/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/object/config/Header.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace object {
namespace config {

Header::Header(const string name, const vector<const ImageMetadata*>* const imageMetadatas) :
		name(name), imageMetadatas(imageMetadatas) {
}

Header::~Header() {
	for (vector<const ImageMetadata*>::const_iterator it = this->imageMetadatas->begin(); it != this->imageMetadatas->end(); it++) {
		const ImageMetadata* imageMetadata = (*it);
		delete imageMetadata;
	}
	delete this->imageMetadatas;
}

const string Header::getName() const {
	return this->name;
}

const vector<const ImageMetadata*>* Header::getImageMetadatas() const {
	return this->imageMetadatas;
}

} /* namespace config */
} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

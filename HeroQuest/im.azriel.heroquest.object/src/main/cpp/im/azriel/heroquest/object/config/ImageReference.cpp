/*
 * ImageReference.cpp
 *
 *  Created on: 24/02/2013
 *      Author: azriel
 */

#include "ImageReference.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace object {
namespace config {

ImageReference::ImageReference(const int id, const int alpha) : id(id), alpha(alpha) {
}

ImageReference::~ImageReference() {
}

const int ImageReference::getId() const {
	return this->id;
}

const int ImageReference::getAlpha() const {
	return this->alpha;
}

} /* namespace config */
} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

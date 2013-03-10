/*
 * ImageReference.cpp
 *
 *  Created on: 24/02/2013
 *      Author: azriel
 */

#include "ImageReference.h"

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

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

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

/*
 * Frame.cpp
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#include "im/azriel/desktop/theme/xml/Frame.h"

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

Frame::Frame(const int wait, const ImageReference* const pic) : wait(wait), pic(pic) {
}

Frame::~Frame() {
	delete this->pic;
}

const ImageReference* const Frame::getPic() const {
	return this->pic;
}

const int Frame::getWait() const {
	return this->wait;
}

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

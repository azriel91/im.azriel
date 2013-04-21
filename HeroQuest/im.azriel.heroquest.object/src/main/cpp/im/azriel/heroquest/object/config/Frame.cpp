/*
 * Frame.cpp
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/object/config/Frame.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace object {
namespace config {

Frame::Frame(const int wait, const ImageReference* const pic) : wait(wait), pic(pic) {
}

Frame::~Frame() {
	delete this->pic;
}

const ImageReference* Frame::getPic() const {
	return this->pic;
}

const int Frame::getWait() const {
	return this->wait;
}

} /* namespace config */
} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

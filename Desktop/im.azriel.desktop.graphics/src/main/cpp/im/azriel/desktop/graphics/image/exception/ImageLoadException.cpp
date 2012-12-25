/*
 * ImageLoadException.cpp
 *
 *  Created on: 11/12/2012
 *      Author: Azriel
 */

#include "ImageLoadException.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {
namespace exception {

ImageLoadException::ImageLoadException(const char* message) : Exception(message) {
}

ImageLoadException::~ImageLoadException() throw() {
}

} /* namespace exception */
} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

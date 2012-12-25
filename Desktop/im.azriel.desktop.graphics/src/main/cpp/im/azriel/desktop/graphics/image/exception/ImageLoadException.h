/*
 * ImageLoadException.h
 *
 *  Created on: 11/12/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_EXCEPTION__IMAGELOADEXCEPTION_H_
#define __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_EXCEPTION__IMAGELOADEXCEPTION_H_

#include "im/azriel/common/exception/Exception.h"

using namespace im::azriel::common::exception;

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace image {
namespace exception {

class ImageLoadException : public Exception {
private:
public:
	ImageLoadException(const char* message);
	virtual ~ImageLoadException() throw();
};

} /* namespace exception */
} /* namespace image */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_GRAPHICS_IMAGE_EXCEPTION__IMAGELOADEXCEPTION_H_ */

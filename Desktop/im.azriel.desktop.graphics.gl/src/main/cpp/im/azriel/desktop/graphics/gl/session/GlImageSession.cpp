/*
 * GlImageSession.cpp
 *
 *  Created on: 18/03/2013
 *      Author: azriel
 */

#include "GlImageSession.h"

namespace im {
namespace azriel {
namespace desktop {
namespace graphics {
namespace gl {
namespace session {

GlImageSession::GlImageSession(const GlPainter* const painter) : ImageSession(painter) {
}

GlImageSession::~GlImageSession() {
}

const GlImage* GlImageSession::doLoadImage(const string path) {
	return GlImageFactory::loadImage(path);
}

const GlImageSheet* GlImageSession::doLoadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
		const int rowCount, const int columnCount) throw (ImageLoadException) {
	return GlImageFactory::loadImageSheet(path, subImageWidth, subImageHeight, rowCount, columnCount);
}

const GlImageSheet* GlImageSession::doLoadImageSheet(const string path, const int subImageWidth, const int subImageHeight,
		const int rowCount, const int columnCount, const int border) throw (ImageLoadException) {
	return GlImageFactory::loadImageSheet(path, subImageWidth, subImageHeight, rowCount, columnCount, border);
}

} /* namespace session */
} /* namespace gl */
} /* namespace graphics */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

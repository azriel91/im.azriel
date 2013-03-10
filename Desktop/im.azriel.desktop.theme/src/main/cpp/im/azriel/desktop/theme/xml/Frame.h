/*
 * Frame.h
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_THEME_XML__FRAME_H_
#define __IM_AZRIEL_DESKTOP_THEME_XML__FRAME_H_

#include "im/azriel/desktop/theme/xml/ImageReference.h"

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

class Frame {
private:
	/**
	 * The number of frames to wait before transitioning to the next frame.
	 */
	const int wait;
	/**
	 * The reference to the image to display on this frame.
	 */
	const ImageReference* const pic;

public:
	Frame(const int wait, const ImageReference* const pic);
	virtual ~Frame();
	/**
	 * Get the reference to the image to display on this frame.
	 *
	 * @return the image reference
	 */
	const ImageReference* const getPic() const;
	/**
	 * Get the number of frames to wait before transitioning to the next frame.
	 *
	 * @return the number of frames to wait
	 */
	const int getWait() const;
};

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_THEME_XML__FRAME_H_ */

/*
 * Frame.h
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__FRAME_H_
#define __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__FRAME_H_

#include "im/azriel/heroquest/object/config/ImageReference.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace object {
namespace config {

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
	const ImageReference* getPic() const;
	/**
	 * Get the number of frames to wait before transitioning to the next frame.
	 *
	 * @return the number of frames to wait
	 */
	const int getWait() const;
};

} /* namespace config */
} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__FRAME_H_ */

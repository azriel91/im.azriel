/*
 * ImageReference.h
 *
 *  Created on: 24/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_THEME_XML__IMAGEREFERENCE_H_
#define __IM_AZRIEL_DESKTOP_THEME_XML__IMAGEREFERENCE_H_

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

class ImageReference {
private:
	/**
	 * The id of the image to display.
	 */
	const int id;
	/**
	 * The multiplier for the alpha component of the image.
	 */
	const int alpha;

public:
	ImageReference(const int id, const int alpha);
	virtual ~ImageReference();
	/**
	 * Get the id of the image to display.
	 *
	 * @return the id
	 */
	const int getId() const;
	/**
	 * Get the multiplier for the alpha component of the image.
	 *
	 * @return the alpha multiplier
	 */
	const int getAlpha() const;
};

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_THEME_XML__IMAGEREFERENCE_H_ */

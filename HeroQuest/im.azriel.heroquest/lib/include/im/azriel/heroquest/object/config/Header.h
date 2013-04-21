/*
 * Header.h
 *
 *  Created on: 22/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__HEADER_H_
#define __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__HEADER_H_

#include <vector>

#include "im/azriel/heroquest/object/config/ImageMetadata.h"

using namespace std;

namespace im {
namespace azriel {
namespace heroquest {
namespace object {
namespace config {

class Header {
private:
	/**
	 * The name specified in the header.
	 */
	const string name;
	/**
	 * The metadatas for images and image sheets.
	 */
	const vector<const ImageMetadata*>* const imageMetadatas;

public:
	Header(const string name, const vector<const ImageMetadata*>* const imageMetadatas);
	virtual ~Header();
	/**
	 * Get the name specified in the header.
	 */
	const string getName() const;
	/**
	 * Get the metadatas for images and image sheets.
	 *
	 * @return the vector of metadata
	 */
	const vector<const ImageMetadata*>* getImageMetadatas() const;
};

} /* namespace config */
} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__HEADER_H_ */

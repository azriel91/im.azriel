/*
 * Reference.h
 *
 *  Created on: 21/04/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING_CONFIG__REFERENCE_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING_CONFIG__REFERENCE_H_

#include <string>

using namespace std;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace loading {
namespace config {

class Reference {
private:
	/**
	 * The id associated with this reference
	 */
	const int id;
	/**
	 * The path stored in this reference
	 */
	const string path;

public:
	Reference(const int id, const string path);
	virtual ~Reference();
	/**
	 * Get the id associated with this reference.
	 *
	 * @return the id
	 */
	const int getId() const;
	/**
	 * Get the path stored in this reference.
	 *
	 * @return the path
	 */
	const string getPath() const;
};

} /* namespace config */
} /* namespace loading */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING_CONFIG__REFERENCE_H_ */

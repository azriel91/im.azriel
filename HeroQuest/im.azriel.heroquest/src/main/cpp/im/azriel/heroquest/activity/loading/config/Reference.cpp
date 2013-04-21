/*
 * Reference.cpp
 *
 *  Created on: 21/04/2013
 *      Author: azriel
 */

#include "Reference.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace loading {
namespace config {

Reference::Reference(const int id, const string path) : id(id), path(path) {
}

Reference::~Reference() {
}

const int Reference::getId() const {
	return this->id;
}

const string Reference::getPath() const {
	return this->path;
}

} /* namespace config */
} /* namespace loading */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

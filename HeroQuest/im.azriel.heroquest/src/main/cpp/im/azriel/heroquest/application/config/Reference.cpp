/*
 * Reference.cpp
 *
 *  Created on: 21/04/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/application/config/Reference.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace application {
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
} /* namespace application */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

/*
 * Actor.cpp
 *
 *  Created on: 13/04/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/object/Object.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace object {

Object::Object(const int id) :
		id(id), x(0), y(0), z(0) {
}

Object::~Object() {
}

} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

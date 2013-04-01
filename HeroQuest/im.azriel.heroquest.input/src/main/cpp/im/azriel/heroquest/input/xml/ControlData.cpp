/*
 * ControlData.cpp
 *
 *  Created on: 30/03/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/input/xml/ControlData.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace input {
namespace xml {

#ifdef ENABLE_LOGGING
Logger* const ControlData::LOGGER = Logger::getLogger("ControlData::LOGGER");
#endif

ControlData::ControlData(const string name, const map<const string, const int>* const keyCodeByControlKeyName) :
		name(name), keyCodeByControlKeyName(keyCodeByControlKeyName) {
}

ControlData::~ControlData() {
	delete this->keyCodeByControlKeyName;
}

const string ControlData::getName() const {
	return this->name;
}

const int ControlData::getKeyCodeForControlKey(const string keyName) const {
	auto const iterator = this->keyCodeByControlKeyName->find(keyName);
	if (iterator == this->keyCodeByControlKeyName->end()) {
#ifdef ENABLE_LOGGING
		LOGGER->error("Key code not defined for key name: [%s]", keyName.c_str());
#endif
		return 0;
	}
	return iterator->second;
}

} /* namespace xml */
} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

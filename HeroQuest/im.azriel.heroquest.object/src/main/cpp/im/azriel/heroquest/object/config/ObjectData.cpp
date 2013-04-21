/*
 * WidgetData.cpp
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/object/config/ObjectData.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace object {
namespace config {

ObjectData::ObjectData(const string id, const Header* const header, const vector<const Sequence*>* const sequences) :
		id(id), header(header), sequences(sequences) {
}

ObjectData::~ObjectData() {
	delete this->header;

	for (auto sequence : *this->sequences) {
		delete sequence;
	}
	delete this->sequences;
}

const Header* ObjectData::getHeader() const {
	return header;
}

const string ObjectData::getId() const {
	return this->id;
}

const vector<const Sequence*>* ObjectData::getSequences() const {
	return sequences;
}

} /* namespace config */
} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

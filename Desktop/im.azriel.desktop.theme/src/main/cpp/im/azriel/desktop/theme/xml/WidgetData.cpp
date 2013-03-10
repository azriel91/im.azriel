/*
 * WidgetData.cpp
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#include "im/azriel/desktop/theme/xml/WidgetData.h"

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

WidgetData::WidgetData(const string id, const Header* const header, const vector<const Sequence*>* const sequences) :
		id(id), header(header), sequences(sequences) {
}

WidgetData::~WidgetData() {
	delete this->header;

	for (auto sequence : *this->sequences) {
		delete sequence;
	}
	delete this->sequences;
}

const Header* const WidgetData::getHeader() const {
	return header;
}

const string WidgetData::getId() const {
	return this->id;
}

const vector<const Sequence*>* const WidgetData::getSequences() const {
	return sequences;
}

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

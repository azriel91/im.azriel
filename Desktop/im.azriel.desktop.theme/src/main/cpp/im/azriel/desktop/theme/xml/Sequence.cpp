/*
 * Sequence.cpp
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#include "im/azriel/desktop/theme/xml/Sequence.h"

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

Sequence::Sequence(const int id, const int nextSequenceId, const vector<const Frame*>* const frames) :
		id(id), nextSequenceId(nextSequenceId), frames(frames) {
}

Sequence::~Sequence() {
	for (auto frame : *this->frames) {
		delete frame;
	}
	delete this->frames;
}

const int Sequence::getId() const {
	return this->id;
}

const int Sequence::getNextSequenceId() const {
	return this->nextSequenceId;
}

const vector<const Frame*>* Sequence::getFrames() const {
	return this->frames;
}

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

/*
 * Sequence.h
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__SEQUENCE_H_
#define __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__SEQUENCE_H_

#include <vector>

#include "im/azriel/heroquest/object/config/Frame.h"

using namespace std;

namespace im {
namespace azriel {
namespace heroquest {
namespace object {
namespace config {

class Sequence {
private:
	/**
	 * The id of this sequence.
	 */
	const int id;
	/**
	 * The id of the next sequence to run.
	 */
	const int nextSequenceId;
	/**
	 * The frames contained by this sequence.
	 */
	const vector<const Frame*>* const frames;

public:
	Sequence(const int id, const int nextSequenceId, const vector<const Frame*>* const frames);
	virtual ~Sequence();
	/**
	 * Get the id of this sequence.
	 *
	 * @return the id
	 */
	const int getId() const;
	/**
	 * Get the id of the next sequence to run.
	 *
	 * @return the next sequence's id
	 */
	const int getNextSequenceId() const;
	/**
	 * Get the frames contained by this sequence.
	 *
	 * @return the frames
	 */
	const vector<const Frame*>* getFrames() const;
};

} /* namespace config */
} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__SEQUENCE_H_ */

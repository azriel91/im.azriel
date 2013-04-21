/*
 * WidgetData.h
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__OBJECTDATA_H_
#define __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__OBJECTDATA_H_

#include <string>
#include <vector>

#include "im/azriel/heroquest/object/config/Header.h"
#include "im/azriel/heroquest/object/config/Sequence.h"

using namespace std;

namespace im {
namespace azriel {
namespace heroquest {
namespace object {
namespace config {

class ObjectData {
private:
	/**
	 * The id of this widget data.
	 */
	const string id;
	/**
	 * The header information for this widget.
	 */
	const Header* const header;
	/**
	 * The sequences defined for this widget.
	 */
	const vector<const Sequence*>* const sequences;

public:
	ObjectData(const string id, const Header* const header, const vector<const Sequence*>* const sequences);
	virtual ~ObjectData();

	/**
	 * Get the header information for this widget.
	 *
	 * @return the header
	 */
	const Header* getHeader() const;
	/**
	 * Get the id of this widget data.
	 *
	 * @return the id
	 */
	const string getId() const;
	/**
	 * Get the sequences defined for this widget.
	 *
	 * @return the sequences
	 */
	const vector<const Sequence*>* getSequences() const;
};

} /* namespace config */
} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_OBJECT_CONFIG__OBJECTDATA_H_ */

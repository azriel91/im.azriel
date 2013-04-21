/*
 * ApplicationConfiguration.h
 *
 *  Created on: 18/04/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING_CONFIG__APPLICATIONCONFIGURATION_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING_CONFIG__APPLICATIONCONFIGURATION_H_

#include <algorithm>
#include <map>
#include <vector>

#include "im/azriel/heroquest/activity/loading/config/Reference.h"
#include "im/azriel/heroquest/object/ObjectType.h"

using namespace std;
using namespace im::azriel::heroquest::object;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace loading {
namespace config {

class ApplicationConfiguration {
private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif

private:
	const vector<const ObjectType*>* const objectTypes;
	const map<const int, const ObjectType*>* const objectTypeById;

public:
	ApplicationConfiguration(const vector<const ObjectType*>* const objectTypes,
	        const map<const int, const ObjectType*>* const objectTypeById);
	virtual ~ApplicationConfiguration();

	const ObjectType* const getObjectType(const int id) const;
	const vector<const ObjectType*>* const getObjectTypes() const;

public:
	static const ApplicationConfiguration* loadFromFile(const string path);
	static const vector<const Reference*>* deserializeReferences(const xml_node node);
	static const Reference* deserializeReference(const xml_node node);
	static const map<const int, const ObjectType*>* loadObjectTypes(const vector<const Reference*>* references);
	static const vector<const ObjectType*>* extractObjectTypes(
	        const map<const int, const ObjectType*>* const objectTypeById);
};

} /* namespace config */
} /* namespace loading */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY_LOADING_CONFIG__APPLICATIONCONFIGURATION_H_ */

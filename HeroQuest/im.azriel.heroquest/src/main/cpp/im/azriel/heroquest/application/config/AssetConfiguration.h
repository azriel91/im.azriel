/*
 * AssetConfiguration.h
 *
 *  Created on: 23/04/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_APPLICATION_CONFIG__ASSETCONFIGURATION_H_
#define __IM_AZRIEL_HEROQUEST_APPLICATION_CONFIG__ASSETCONFIGURATION_H_

#include <cstdlib>
#include <map>
#include <vector>

#include "im/azriel/common/logger/Logger.h"
#include "im/azriel/heroquest/application/config/Reference.h"
#include "pugixml-1.2/pugixml.hpp"

using namespace std;
using namespace pugi;
using namespace im::azriel::common::logger;

namespace im {
namespace azriel {
namespace heroquest {
namespace application {
namespace config {

class AssetConfiguration {
private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif
	/**
	 * The references to the object type configurations.
	 */
	const vector<const Reference*>* objectReferences;

public:
	virtual ~AssetConfiguration();
	/**
	 * Get the references to the object type configurations.
	 *
	 * @return the references
	 */
	const vector<const Reference*>* getObjectReferences() const;

private:
	AssetConfiguration(const vector<const Reference*>* objectReferences);

public:
	static const AssetConfiguration* loadFromFile(const string path);
	static const vector<const Reference*>* deserializeReferences(const xml_node node);
	static const Reference* deserializeReference(const xml_node node);
};

} /* namespace config */
} /* namespace application */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_HEROQUEST_APPLICATION_CONFIG__ASSETCONFIGURATION_H_ */

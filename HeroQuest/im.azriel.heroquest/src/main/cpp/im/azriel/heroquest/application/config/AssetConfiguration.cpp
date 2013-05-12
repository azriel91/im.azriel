/*
 * AssetConfiguration.cpp
 *
 *  Created on: 23/04/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/application/config/AssetConfiguration.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace application {
namespace config {

#ifdef ENABLE_LOGGING
Logger* const AssetConfiguration::LOGGER = Logger::getLogger("AssetConfiguration::LOGGER");
#endif

AssetConfiguration::AssetConfiguration(const vector<const Reference*>* objectReferences) :
		objectReferences(objectReferences) {
}

AssetConfiguration::~AssetConfiguration() {
	for (auto const reference : *this->objectReferences) {
		delete reference;
	}
	delete this->objectReferences;
}

const vector<const Reference*>* AssetConfiguration::getObjectReferences() const {
	return this->objectReferences;
}

const AssetConfiguration* AssetConfiguration::loadFromFile(const string path) {
	xml_document doc;
	const xml_parse_result result = doc.load_file(path.c_str());
#ifdef ENABLE_LOGGING
	LOGGER->info("Loaded [%s]. Result: [%s]", path.c_str(), result.description());
#endif

	xml_node configurationNode = doc.root().child("configuration");
	xml_node objectsNode = configurationNode.child("objects");

	auto const objectReferences = deserializeReferences(objectsNode);

	return new AssetConfiguration(objectReferences);
}

const vector<const Reference*>* AssetConfiguration::deserializeReferences(const xml_node node) {
	auto const references = new vector<const Reference*>();
	auto referenceNodes = node.children("references");
	for (const xml_node referenceNode : referenceNodes) {
		auto const reference = deserializeReference(referenceNode);
		references->push_back(reference);
	}
	return references;
}

const Reference* AssetConfiguration::deserializeReference(const xml_node node) {
	const xml_attribute idAttribute = node.attribute("id");
	const int id = idAttribute.as_int();

	const xml_attribute pathAttribute = node.attribute("path");
	const string path(pathAttribute.as_string());
	if (path.empty()) {
#ifdef ENABLE_LOGGING
		LOGGER->error("The \"path\" attribute is a required field for %s", node.path('/').c_str());
#endif
		exit(1);
	}

	return new Reference(id, path);
}

} /* namespace config */
} /* namespace application */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

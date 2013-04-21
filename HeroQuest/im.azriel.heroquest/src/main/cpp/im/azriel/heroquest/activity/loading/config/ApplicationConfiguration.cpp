/*
 * ObjectConfiguration.cpp
 *
 *  Created on: 18/04/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/activity/loading/config/ApplicationConfiguration.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace loading {
namespace config {

#ifdef ENABLE_LOGGING
Logger* const ApplicationConfiguration::LOGGER = Logger::getLogger("ApplicationConfiguration::LOGGER");
#endif

ApplicationConfiguration::ApplicationConfiguration(const vector<const ObjectType*>* const objectTypes,
        const map<const int, const ObjectType*>* const objectTypeById) :
		objectTypes(objectTypes), objectTypeById(objectTypeById) {
}

ApplicationConfiguration::~ApplicationConfiguration() {

	// we only have to delete the object types from the vector because the map points to the same instances
	for (auto const objectType : *this->objectTypes) {
		delete objectType;
	}
	delete this->objectTypes;
	delete this->objectTypeById;
}

const ApplicationConfiguration* ApplicationConfiguration::loadFromFile(const string path) {
	xml_document doc;
	const xml_parse_result result = doc.load_file(path.c_str());
#ifdef ENABLE_LOGGING
	LOGGER->info("Loaded [%s]. Result: [%s]", path.c_str(), result.description());
#endif

	xml_node configurationNode = doc.root().child("configuration");
	xml_node objectsNode = configurationNode.child("objects");

	auto const objectReferences = deserializeReferences(objectsNode);
	auto const objectTypeById = loadObjectTypes(objectReferences);

	for (auto const reference : *objectReferences) {
		delete reference;
	}
	delete objectReferences;

	auto const objectTypes = extractObjectTypes(objectTypeById);
	return new ApplicationConfiguration(objectTypes, objectTypeById);
}

const vector<const Reference*>* ApplicationConfiguration::deserializeReferences(const xml_node node) {
	auto const references = new vector<const Reference*>();
	auto referenceNodes = node.children("references");
	for (const xml_node referenceNode : referenceNodes) {
		auto const reference = deserializeReference(referenceNode);
		references->push_back(reference);
	}
	return references;
}

const Reference* ApplicationConfiguration::deserializeReference(const xml_node node) {
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

const map<const int, const ObjectType*>* ApplicationConfiguration::loadObjectTypes(
        const vector<const Reference*>* references) {
	auto const objectTypeById = new map<const int, const ObjectType*>();
	for (auto const reference : *references) {
		const int id = reference->getId();
		const string path = reference->getPath();

		auto const objectType = ObjectType::loadFromFile(path, id);
		objectTypeById->insert(make_pair(id, objectType));
	}
	return objectTypeById;
}

const vector<const ObjectType*>* ApplicationConfiguration::extractObjectTypes(
        const map<const int, const ObjectType*>* const objectTypeById) {
	auto const values = new vector<const ObjectType*>();
	for (auto const entry : *objectTypeById) {
		values->push_back(entry.second);
	}
	return values;
}

} /* namespace config */
} /* namespace loading */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

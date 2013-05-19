/*
 * ObjectConfiguration.cpp
 *
 *  Created on: 18/04/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/application/config/ApplicationConfiguration.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace application {
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

const ApplicationConfiguration* ApplicationConfiguration::loadApplicationConfiguration(
        const AssetConfiguration* const assetConfiguration) {
	auto const objectReferences = assetConfiguration->getObjectReferences();
	auto const objectTypeById = loadObjectTypes(objectReferences);

	auto const objectTypes = extractObjectTypes(objectTypeById);
	return new ApplicationConfiguration(objectTypes, objectTypeById);
}

Job<const ApplicationConfiguration*>* ApplicationConfiguration::loadApplicationConfigurationAsJob(
        const AssetConfiguration* const assetConfiguration) {
	return new ConfigLoadingJob(assetConfiguration);
}

const map<const int, const ObjectType*>* ApplicationConfiguration::loadObjectTypes(
        const vector<const Reference*>* const references) {
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

ApplicationConfiguration::ConfigLoadingJob::ConfigLoadingJob(const AssetConfiguration* const assetConfiguration) :
		assetConfiguration(assetConfiguration) {
}

ApplicationConfiguration::ConfigLoadingJob::~ConfigLoadingJob() {
}

const ApplicationConfiguration* ApplicationConfiguration::ConfigLoadingJob::doWork() {
	auto const objectReferences = this->assetConfiguration->getObjectReferences();
	auto const objectTypeById = ConfigLoadingJob::loadObjectTypes(objectReferences);

	auto const objectTypes = extractObjectTypes(objectTypeById);
	return new ApplicationConfiguration(objectTypes, objectTypeById);
}

const map<const int, const ObjectType*>* ApplicationConfiguration::ConfigLoadingJob::loadObjectTypes(
        const vector<const Reference*>* const references) {
	auto const objectTypeById = new map<const int, const ObjectType*>();
	stringstream statusMessageStream;

	for (auto const reference : *references) {
		const int id = reference->getId();
		const string path = reference->getPath();

		statusMessageStream.str(string()); // clear the stream
		statusMessageStream << "Loading " << path;
		setStatusMessage(statusMessageStream.str());

		auto const objectType = ObjectType::loadFromFile(path, id);
		objectTypeById->insert(make_pair(id, objectType));
	}

	return objectTypeById;
}

} /* namespace config */
} /* namespace application */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

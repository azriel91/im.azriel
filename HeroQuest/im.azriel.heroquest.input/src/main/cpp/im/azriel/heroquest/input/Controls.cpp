/*
 * Controls.cpp
 *
 *  Created on: 31/03/2013
 *      Author: azriel
 */

#include "Controls.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

#ifdef ENABLE_LOGGING
Logger* const Controls::LOGGER = Logger::getLogger("Controls::LOGGER");
#endif

Controls::Controls(const vector<const ControlData*>* const controlDatas) : controlDatas(controlDatas) {
}

Controls::~Controls() {
	for (auto const controlData : *this->controlDatas) {
		delete controlData;
	}
	delete this->controlDatas;
}

const vector<const ControlData*>* Controls::getControlDatas() const {
	return this->controlDatas;
}

Controls* Controls::loadFromFile(const string path) {
	auto const controlDatas = new vector<const ControlData*>();

	xml_document doc;
	const xml_parse_result result = doc.load_file(path.c_str());

#ifdef ENABLE_LOGGING
	LOGGER->info("Loaded [%s]. Result: [%s]", path.c_str(), result.description());
#endif

	xml_node themeNode = doc.root().child("controls");

	// load control data
	const auto controllerNodes = themeNode.children("controller");
	for (const xml_node controllerNode : controllerNodes) {
		const ControlData* const controlData = deserializeControlData(controllerNode);
		controlDatas->push_back(controlData);
	}

	return new Controls(controlDatas);
}

const ControlData* Controls::deserializeControlData(const xml_node node) {
	auto const keyMappings = new map<const string, const int>();

	const xml_attribute nameAttribute = node.attribute("name");
	const string name(nameAttribute.as_string());

	const auto controllerNodes = node.children("controlKey");
	for (const xml_node controllerNode : controllerNodes) {
		const xml_attribute controlKeyNameAttribute = controllerNode.attribute("name");
		const string controlKeyName(controlKeyNameAttribute.as_string());

		const xml_attribute keyCodeAttribute = controllerNode.attribute("keyCode");
		const int keyCode = keyCodeAttribute.as_int(0);

		keyMappings->insert(make_pair(controlKeyName, keyCode));
	}

	return new ControlData(name, keyMappings);
}

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

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

Controls::Controls(
        const set<KeyboardSynchronizedControlKeyInputSource*>* const keyboardSynchronizedControlKeyInputSources) :
		        keyboardSynchronizedControlKeyInputSources(keyboardSynchronizedControlKeyInputSources),
		        controlKeyInputSources(collateControlKeyInputSources()) {
}

Controls::~Controls() {
	for (auto const controlKeyInputSource : *this->controlKeyInputSources) {
		delete controlKeyInputSource;
	}
	delete this->controlKeyInputSources;

	delete this->keyboardSynchronizedControlKeyInputSources;
}

const set<SynchronizedControlKeyInputSource*>* Controls::getControlKeyInputSources() const {
	return this->controlKeyInputSources;
}

const set<KeyboardSynchronizedControlKeyInputSource*>* Controls::getKeyboardSynchronizedControlKeyInputSources() const {
	return this->keyboardSynchronizedControlKeyInputSources;
}

const set<SynchronizedControlKeyInputSource*>* Controls::collateControlKeyInputSources() const {
	auto const controlKeyInputSources = new set<SynchronizedControlKeyInputSource*>();
	controlKeyInputSources->insert(
			this->keyboardSynchronizedControlKeyInputSources->begin(),
	        this->keyboardSynchronizedControlKeyInputSources->end());
	return controlKeyInputSources;
}

Controls* Controls::loadFromFile(const string path) {
	auto const controlDatas = deserializeControls(path);
	auto const keyboardSynchronizedControlKeyInputSources = new set<KeyboardSynchronizedControlKeyInputSource*>();

	int* const keyCodes = new int[ControlKeyCode::BUTTON_COUNT];
	for (auto const controlData : *controlDatas) {
		keyCodes[ControlKeyCode::UP] = controlData->getKeyCodeForControlKey("up");
		keyCodes[ControlKeyCode::DOWN] = controlData->getKeyCodeForControlKey("down");
		keyCodes[ControlKeyCode::LEFT] = controlData->getKeyCodeForControlKey("left");
		keyCodes[ControlKeyCode::RIGHT] = controlData->getKeyCodeForControlKey("right");
		keyCodes[ControlKeyCode::ATTACK] = controlData->getKeyCodeForControlKey("attack");
		keyCodes[ControlKeyCode::JUMP] = controlData->getKeyCodeForControlKey("jump");
		keyCodes[ControlKeyCode::DEFEND] = controlData->getKeyCodeForControlKey("defend");
		keyboardSynchronizedControlKeyInputSources->insert(new KeyboardSynchronizedControlKeyInputSource(keyCodes));
	}

	return new Controls(keyboardSynchronizedControlKeyInputSources);
}

const vector<const ControlData*>* Controls::deserializeControls(const string path) {
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

	return controlDatas;
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

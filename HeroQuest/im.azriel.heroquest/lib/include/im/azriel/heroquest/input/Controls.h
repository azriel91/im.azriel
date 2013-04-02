/*
 * Controls.h
 *
 *  Created on: 31/03/2013
 *      Author: azriel
 */

#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "im/azriel/common/logger/Logger.h"
#include "im/azriel/heroquest/input/xml/ControlData.h"
#include "im/azriel/heroquest/input/keyboard/KeyboardSynchronizedControlKeyInputSource.h"
#include "pugixml-1.2/pugixml.hpp"

using namespace std;
using namespace im::azriel::common::logger;
using namespace im::azriel::heroquest::input::xml;
using namespace im::azriel::heroquest::input::keyboard;
using namespace pugi;

namespace im {
namespace azriel {
namespace heroquest {
namespace input {

class Controls {
private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif

private:
	/**
	 * The keyboard synchronized control key input sources loaded from the control settings file.
	 */
	const set<KeyboardSynchronizedControlKeyInputSource*>* const keyboardSynchronizedControlKeyInputSources;
	/**
	 * All loaded control key input sources.
	 */
	const set<SynchronizedControlKeyInputSource*>* const controlKeyInputSources;

public:
	virtual ~Controls();

	/**
	 * Gets all of the control key input sources loaded by this Controls object.
	 *
	 * @return the control key input sources
	 */
	const set<SynchronizedControlKeyInputSource*>* getControlKeyInputSources() const;
	/**
	 * Get the keyboard synchronized control key input sources loaded from the control settings file.
	 *
	 * @return the keyboard synchronized control key input sources
	 */
	const set<KeyboardSynchronizedControlKeyInputSource*>* getKeyboardSynchronizedControlKeyInputSources() const;

private:
	Controls(const set<KeyboardSynchronizedControlKeyInputSource*>* const keyboardSynchronizedControlKeyInputSources);
	const set<SynchronizedControlKeyInputSource*>* collateControlKeyInputSources() const;

public:
	static Controls* loadFromFile(const string path);

private:
	static const vector<const ControlData*>* deserializeControls(const string path);
	static const ControlData* deserializeControlData(const xml_node node);
};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* CONTROLS_H_ */

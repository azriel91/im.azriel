/*
 * ControlData.h
 *
 *  Created on: 30/03/2013
 *      Author: azriel
 */

#ifndef CONTROLDATA_H_
#define CONTROLDATA_H_

#include <map>
#include <string>

#include "im/azriel/common/logger/Logger.h"

using namespace std;

using namespace im::azriel::common::logger;

namespace im {
namespace azriel {
namespace heroquest {
namespace input {
namespace xml {

class ControlData {
private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif

private:
	/**
	 * The name registered for this controller.
	 */
	const string name;
	/**
	 * Mappings of control key names to the keyboard key codes.
	 */
	const map<const string, const int>* const keyCodeByControlKeyName;

public:
	ControlData(const string name, const map<const string, const int>* const keyCodeByControlKeyName);
	virtual ~ControlData();
	/**
	 * Gets the name registered for this controller.
	 *
	 * @return the name
	 */
	const string getName() const;
	/**
	 * Gets the key code registered for the specified control key.
	 *
	 * @param keyName the name of the control key
	 * @return the key code
	 */
	const int getKeyCodeForControlKey(const string keyName) const;
};

} /* namespace xml */
} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* CONTROLDATA_H_ */

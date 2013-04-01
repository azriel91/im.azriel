/*
 * Controls.h
 *
 *  Created on: 31/03/2013
 *      Author: azriel
 */

#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <map>
#include <string>
#include <vector>

#include "im/azriel/heroquest/input/xml/ControlData.h"
#include "im/azriel/common/logger/Logger.h"
#include "pugixml-1.2/pugixml.hpp"

using namespace std;
using namespace im::azriel::common::logger;
using namespace im::azriel::heroquest::input::xml;
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
	 * The control datas loaded from the control settings file.
	 */
	const vector<const ControlData*>* const controlDatas;

public:
	virtual ~Controls();
	/**
	 * Get the control datas loaded from the control settings file.
	 *
	 * @return the control datas
	 */
	const vector<const ControlData*>* getControlDatas() const;

private:
	Controls(const vector<const ControlData*>* const controlDatas);

public:
	static Controls* loadFromFile(const string path);

private:
	static const ControlData* deserializeControlData(const xml_node node);
};

} /* namespace input */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* CONTROLS_H_ */

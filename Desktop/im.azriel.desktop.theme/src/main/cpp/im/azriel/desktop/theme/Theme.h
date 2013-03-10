/*
 * Theme.h
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_THEME__THEME_H_
#define __IM_AZRIEL_DESKTOP_THEME__THEME_H_

#include <cmath>
#include <cstdlib>
#include <map>
#include <string>

#include "im/azriel/common/logger/Logger.h"
#include "im/azriel/desktop/theme/xml/Header.h"
#include "im/azriel/desktop/theme/xml/Frame.h"
#include "im/azriel/desktop/theme/xml/ImageMetadata.h"
#include "im/azriel/desktop/theme/xml/ImageReference.h"
#include "im/azriel/desktop/theme/xml/Sequence.h"
#include "im/azriel/desktop/theme/xml/WidgetData.h"
#include "pugixml-1.2/pugixml.hpp"

using namespace std;
using namespace im::azriel::common::logger;
using namespace im::azriel::desktop::theme::xml;
using namespace pugi;

namespace im {
namespace azriel {
namespace desktop {
namespace theme {

class Theme {
private:
	static constexpr int XML_SCHEMA_MISMATCH = 1000;
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif
	/**
	 * Mappings of arbitrary string values by id
	 */
	const map<const string, const string>* const constantsById;
	/**
	 * Mappings of widget data by their id.
	 */
	const map<const string, const WidgetData*>* const widgetDataById;

public:
	virtual ~Theme();
	/**
	 * Get the string constant defined
	 */
	const string getConstant(const string id) const;
	/**
	 * Get the widget data for the given id.
	 *
	 * @return the widget data
	 */
	const WidgetData* getWidgetData(const string id) const;

private:
	Theme(const map<const string, const string>* const constantsById,
	        const map<const string, const WidgetData*>* const widgetDataById);

public:
	static const Theme* loadFromFile(const string path);

private:
	static const WidgetData* deserializeWidgetData(const xml_node node);
	static const Header* deserializeHeader(const xml_node node);
	static const ImageMetadata* deserializeImageMetadata(const xml_node node);
	static const Sequence* deserializeSequence(const xml_node node);
	static const Frame* deserializeFrame(const xml_node node);
	static const ImageReference* deserializeImageReference(const xml_node node);
};

} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_THEME__THEME_H_ */

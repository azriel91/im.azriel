/*
 * WidgetData.h
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_DESKTOP_THEME_XML__WIDGETDATA_H_
#define __IM_AZRIEL_DESKTOP_THEME_XML__WIDGETDATA_H_

#include <string>
#include <vector>

#include "im/azriel/desktop/theme/xml/Header.h"
#include "im/azriel/desktop/theme/xml/Sequence.h"

using namespace std;

namespace im {
namespace azriel {
namespace desktop {
namespace theme {
namespace xml {

class WidgetData {
private:
	/**
	 * The id of this widget data.
	 */
	const string id;
	/**
	 * The header information for this widget.
	 */
	const Header* const header;
	/**
	 * The sequences defined for this widget.
	 */
	const vector<const Sequence*>* const sequences;

public:
	WidgetData(const string id, const Header* const header, const vector<const Sequence*>* const sequences);
	virtual ~WidgetData();

	/**
	 * Get the header information for this widget.
	 *
	 * @return the header
	 */
	const Header* getHeader() const;
	/**
	 * Get the id of this widget data.
	 *
	 * @return the id
	 */
	const string getId() const;
	/**
	 * Get the sequences defined for this widget.
	 *
	 * @return the sequences
	 */
	const vector<const Sequence*>* getSequences() const;
};

} /* namespace xml */
} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_DESKTOP_THEME_XML__WIDGETDATA_H_ */

/*
 * MenuItem.h
 *
 *  Created on: 28/03/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY_WIDGET__MENUITEM_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY_WIDGET__MENUITEM_H_

#include "im/azriel/heroquest/activity/widget/Widget.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace widget {

class MenuItem : public Widget {
private:
	static constexpr int TRANSITION_TO_ACTIVE_SEQUENCE = 1;
	static constexpr int TRANSITION_TO_INACTIVE_SEQUENCE = 3;

private:
	/**
	 * Whether this menu item has focus.
	 */
	bool focused;

public:
	MenuItem(const GlPainter* const painter, const WidgetData* const widgetData);
	virtual ~MenuItem();
	/**
	 * Method called at the beginning of the #update() method.
	 */
	virtual void doUpdate();
	/**
	 * Sets the focused state of this menu item.
	 *
	 * @param focused whether this menu item is focused
	 */
	void setFocused(const bool focused);
};

} /* namespace widget */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY_WIDGET__MENUITEM_H_ */

/*
 * MenuItem.cpp
 *
 *  Created on: 28/03/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/activity/widget/MenuItem.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace widget {

constexpr int MenuItem::TRANSITION_TO_ACTIVE_SEQUENCE;
constexpr int MenuItem::TRANSITION_TO_INACTIVE_SEQUENCE;

MenuItem::MenuItem(const GlPainter* const painter, const WidgetData* const widgetData) :
		Widget(painter, widgetData), focused(false) {
}

MenuItem::~MenuItem() {
}

void MenuItem::doUpdate() {
}

void MenuItem::setFocused(const bool focused) {
	if (this->focused == focused) {
		return;
	}
	this->focused = focused;
	selectSequence(this->focused ? TRANSITION_TO_ACTIVE_SEQUENCE : TRANSITION_TO_INACTIVE_SEQUENCE);
}

} /* namespace widget */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

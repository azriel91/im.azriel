/*
 * Widget.cpp
 *
 *  Created on: 9/03/2013
 *      Author: azriel
 */

#include "Widget.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace widget {

Widget::Widget(const GlPainter* const painter, const WidgetData* const widgetData) :
		painter(painter), data(widgetData), x(0), y(0) {
}

Widget::~Widget() {
}

const int Widget::getX() const {
	return this->x;
}

const int Widget::getY() const {
	return this->y;
}

void Widget::setX(const int x) {
	this->x = x;
}

void Widget::setY(const int y) {
	this->y = y;
}

void Widget::setCoordinates(const int x, const int y) {
	this->x = x;
	this->y = y;
}

void Widget::update() {
	// do nothing
}


} /* namespace widget */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

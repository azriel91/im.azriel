/*
 * Widget.h
 *
 *  Created on: 9/03/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ACTIVITY_WIDGET__WIDGET_H_
#define __IM_AZRIEL_HEROQUEST_ACTIVITY_WIDGET__WIDGET_H_

#include "im/azriel/desktop/theme/xml/WidgetData.h"
#include "im/azriel/desktop/graphics/gl/painter/GlPainter.h"

using namespace im::azriel::desktop::graphics::gl::painter;
using namespace im::azriel::desktop::theme::xml;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace widget {

class Widget {
private:
	/**
	 * Painter to paint images.
	 */
	const GlPainter* const painter;
	/**
	 * The widget data specifying the behaviour of this widget.
	 */
	const WidgetData* const data;
	/**
	 * The x coordinate of this widget relative to its parent.
	 */
	int x;
	/**
	 * The y coordinate of this widget relative to its parent.
	 */
	int y;

public:
	Widget(const GlPainter* const painter, const WidgetData* const widgetData);
	virtual ~Widget();
	/**
	 * Get the x coordinate of this widget relative to its parent.
	 *
	 * @return the x coordinate
	 */
	const int getX() const;
	/**
	 * Get the y coordinate of this widget relative to its parent.
	 *
	 * @return the y coordinate
	 */
	const int getY() const;
	/*
	 * Redraws this widget on screen.
	 */
	virtual void redraw() const = 0;
	/**
	 * Sets the x coordinate of this widget.
	 *
	 * @param x the x coordinate
	 */
	void setX(const int x);
	/**
	 * Sets the y coordinate of this widget.
	 *
	 * @param y the y coordinate
	 */
	void setY(const int y);
	/**
	 * Sets the x and y coordinates of this widget.
	 *
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	void setCoordinates(const int x, const int y);
	/**
	 * Method called every frame. The default implementation does nothing.
	 */
	virtual void update();
};

} /* namespace widget */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY_WIDGET__WIDGET_H_ */

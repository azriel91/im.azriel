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
#include "im/azriel/desktop/graphics/gl/session/GlImageSession.h"

using namespace im::azriel::desktop::graphics::gl::painter;
using namespace im::azriel::desktop::graphics::gl::session;
using namespace im::azriel::desktop::theme::xml;

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace widget {

class Widget {
private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif

protected:
	/**
	 * Value indicating that the next sequence should be the sequence with id="0".
	 */
	static constexpr int FIRST_SEQUENCE = 999;
	/**
	 * Value indicating that the when the current sequence ends, the sequence will stay on the last frame.
	 */
	static constexpr int NO_NEXT = 0;

protected:
	/**
	 * Painter to paint images.
	 */
	const GlPainter* const painter;
	/**
	 * The widget data specifying the behaviour of this widget.
	 */
	const WidgetData* const data;
	/**
	 * The image session that tracks this widget's images.
	 */
	const GlImageSession* const imageSession;
	/**
	 * The current sequence that this widget is on.
	 */
	const Sequence* currentSequence;
	/**
	 * The id of the currently active frame.
	 */
	unsigned int currentFrameId;
	/**
	 * Logical clock to keep track of this widget's state in its current sequence.
	 */
	int clock;
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
	/**
	 * Redraws this widget on screen.
	 */
	virtual void redraw() const;
	/**
	 * Whether or not this widget's current sequence is still running. This will only return {@code true} iff this
	 * widget is on the final frame of its current sequence, has past the time to wait for that frame, and there is no
	 * next sequence to run.
	 *
	 * @return {@code true} has completed animating, {@code false} otherwise
	 */
	const bool hasCompletedAnimation() const;
	/**
	 * Updates this widget to use the sequence of the specified sequence id.
	 *
	 * @param sequenceId the id of the sequence to run
	 */
	void selectSequence(const unsigned int sequenceId);
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
	 * Updates the state of the current sequence.
	 */
	void update();

protected:
	/**
	 * Method called at the beginning of the #update() method.
	 */
	virtual void doUpdate() = 0;

private:
	GlImageSession* initializeImageSession();
	const Sequence* initializeFirstSequence();
};

} /* namespace widget */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ACTIVITY_WIDGET__WIDGET_H_ */

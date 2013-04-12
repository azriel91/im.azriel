/*
 * Widget.cpp
 *
 *  Created on: 9/03/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/activity/widget/Widget.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace activity {
namespace widget {

#ifdef ENABLE_LOGGING
Logger* const Widget::LOGGER = Logger::getLogger("Widget::LOGGER");
#endif

Widget::Widget(const GlPainter* const painter, const WidgetData* const widgetData) :
		        painter(painter),
		        data(widgetData),
		        imageSession(initializeImageSession()),
		        currentSequence(initializeFirstSequence()),
		        currentFrameId(0),
		        clock(-1),
		        x(0),
		        y(0) {
}

Widget::~Widget() {
}

const int Widget::getX() const {
	return this->x;
}

const int Widget::getY() const {
	return this->y;
}

void Widget::redraw() const {
	auto const frames = this->currentSequence->getFrames();
	auto const currentFrame = frames->at(this->currentFrameId);
	auto const imageReference = currentFrame->getPic();

	const int imageId = imageReference->getId();
	const int alpha = imageReference->getAlpha();

	this->imageSession->paint(imageId, this->x, this->y, 255, 255, 255, alpha);
}

const bool Widget::hasCompletedAnimation() const {
	auto const frames = this->currentSequence->getFrames();
	auto const currentFrame = frames->at(this->currentFrameId);
	return this->currentFrameId == frames->size() - 1 && //
			this->clock >= currentFrame->getWait() && //
			this->currentSequence->getNextSequenceId() == NO_NEXT;
}

void Widget::selectSequence(const unsigned int sequenceId) {
	auto const sequences = this->data->getSequences();
	if (sequenceId < 0 || sequences->size() < sequenceId) {
#ifdef ENABLE_LOGGING
		LOGGER->error("Invalid sequence id: [%d] specified for widget: [%s]", sequenceId, this->data->getId().c_str());
#endif
		return;
	}

	this->currentSequence = sequences->at(sequenceId);
	this->currentFrameId = 0;
	this->clock = -1;
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
	doUpdate();

	auto const frames = this->currentSequence->getFrames();
	auto currentFrame = frames->at(this->currentFrameId);

	if (this->clock < currentFrame->getWait()) {
		this->clock++;
		return;
	}

	// we have passed the time to wait on the current frame

	// if we have more frames in this sequence, we go to the next frame
	if (this->currentFrameId < frames->size() - 1) {
		this->currentFrameId++;
		this->clock = -1;

	} else if (this->currentFrameId == frames->size() - 1) {
		// we are on the last frame
		auto const sequences = this->data->getSequences();
		int nextSequenceId = this->currentSequence->getNextSequenceId();

		switch (nextSequenceId) {
			// if the sequence does not loop, we stop
			case NO_NEXT:
				break;

			case FIRST_SEQUENCE:
				this->currentSequence = sequences->at(0);
				this->currentFrameId = 0;
				this->clock = -1;
				break;

			default:
				this->currentSequence = sequences->at(nextSequenceId);
				this->currentFrameId = 0;
				this->clock = -1;
				break;
		}
	}
}

GlImageSession* Widget::initializeImageSession() {
	const Header* const header = this->data->getHeader();

	auto const imageMetadatas = header->getImageMetadatas();
	GlImageSession* const imageSession = new GlImageSession(this->painter);
	for (auto const imageMetadata : *imageMetadatas) {
		if (imageMetadata->isImageSheet()) {
			imageSession->loadImageSheet(imageMetadata->getPath(), imageMetadata->getSubImageWidth(),
			        imageMetadata->getSubImageHeight(), imageMetadata->getRowCount(), imageMetadata->getColumnCount());
		} else {
			imageSession->loadImage(imageMetadata->getPath());
		}
	}

	return imageSession;
}

const Sequence* Widget::initializeFirstSequence() {
	auto const sequences = this->data->getSequences();
	if (sequences->size() == 0) {
#ifdef ENABLE_LOGGING
		LOGGER->error("No sequences defined for widget: %s", this->data->getId().c_str());
#endif
		exit(1);
	}
	return sequences->at(0);
}

} /* namespace widget */
} /* namespace activity */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

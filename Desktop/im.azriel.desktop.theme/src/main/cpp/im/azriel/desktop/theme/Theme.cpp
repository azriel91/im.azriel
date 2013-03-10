/*
 * Theme.cpp
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#include "im/azriel/desktop/theme/Theme.h"

namespace im {
namespace azriel {
namespace desktop {
namespace theme {

#ifdef ENABLE_LOGGING
Logger* const Theme::LOGGER = Logger::getLogger("Theme::LOGGER");
#endif

Theme::~Theme() {
	delete this->constantsById;
	for (auto entry : *this->widgetDataById) {
		delete entry.second;
	}
	delete this->widgetDataById;
}

const string Theme::getConstant(const string id) const {
	return this->constantsById->at(id);
}

const WidgetData* Theme::getWidgetData(const string id) const {
	return this->widgetDataById->at(id);
}

Theme::Theme(const map<const string, const string>* const constantsById,
        const map<const string, const WidgetData*>* const widgetDataById) :
		constantsById(constantsById), widgetDataById(widgetDataById) {
}

const Theme* Theme::loadFromFile(const string path) {
	auto constantsById = new map<const string, const string>();
	auto widgetDataById = new map<const string, const WidgetData*>();

	xml_document doc;
	const xml_parse_result result = doc.load_file(path.c_str());
#ifdef ENABLE_LOGGING
	LOGGER->info("Loaded [%s]. Result: [%s]", path.c_str(), result.description());
#endif

	xml_node themeNode = doc.root().child("theme");

	// load constants
	const auto constantNodes = themeNode.children("constant");
	for (const xml_node constantNode : constantNodes) {
		const xml_attribute idAttribute = constantNode.attribute("id");
		const string id(idAttribute.as_string());

		const xml_attribute valueAttribute = constantNode.attribute("value");
		const string value(valueAttribute.as_string());
		constantsById->insert(make_pair(id, value));
	}

	// load widget data
	const auto widgetNodes = themeNode.children("widget");
	for (const xml_node widgetNode : widgetNodes) {
		const WidgetData* const widgetData = deserializeWidgetData(widgetNode);
		widgetDataById->insert(make_pair(widgetData->getId(), widgetData));
	}

	return new Theme(constantsById, widgetDataById);
}

const WidgetData* Theme::deserializeWidgetData(const xml_node node) {
	const xml_attribute idAttribute = node.attribute("id");
	const string id(idAttribute.as_string());

	const xml_node headerNode = node.child("header");
	const Header* header = deserializeHeader(headerNode);

	auto const sequences = new vector<const Sequence*>(1);
	auto sequenceNodes = node.children("sequence");
	for (const xml_node sequenceNode : sequenceNodes) {
		auto const sequence = deserializeSequence(sequenceNode);
		const int id = sequence->getId();
		auto size = sequences->size();

		// ensure sufficient capacity
		if (size <= (unsigned int) id) {
			const double val = log2((double) id);
			const int newSize = 2 << (int) (ceil(val));
			sequences->resize(newSize);
		}
		sequences->at(id) = sequence;
	}

	return new WidgetData(id, header, sequences);
}

const Header* Theme::deserializeHeader(const xml_node node) {
	auto const imageMetadatas = new vector<const ImageMetadata*>();
	const auto imageNodes = node.children("image");
	for (const xml_node imageNode : imageNodes) {
		auto const imageMetadata = deserializeImageMetadata(imageNode);
		imageMetadatas->push_back(imageMetadata);
	}

	return new Header(imageMetadatas);
}

const ImageMetadata* Theme::deserializeImageMetadata(const xml_node node) {
	const xml_attribute pathAttribute = node.attribute("path");
	const string path(pathAttribute.as_string());
	if (path.empty()) {
#ifdef ENABLE_LOGGING
		LOGGER->error("The \"path\" attribute is a required field for %s", node.path('/').c_str());
#endif
		exit(XML_SCHEMA_MISMATCH);
	}

	const xml_attribute widthAttribute = node.attribute("width");
	const int width = widthAttribute.as_int(-1);

	const xml_attribute heightAttribute = node.attribute("height");
	const int height = heightAttribute.as_int(-1);

	// if width or height is below zero, we assume this is a single image
	if (width < 0 || height < 0) {
		return new ImageMetadata(path);
	}

	const xml_attribute rowCountAttribute = node.attribute("rows");
	const int rowCount = rowCountAttribute.as_int(1);

	const xml_attribute columnCountAttribute = node.attribute("columns");
	const int columnCount = columnCountAttribute.as_int(1);

	return new ImageMetadata(path, width, height, rowCount, columnCount);
}

const Sequence* Theme::deserializeSequence(const xml_node node) {
	const xml_attribute idAttribute = node.attribute("id");
	const int id = idAttribute.as_int();

	const xml_attribute nextAttribute = node.attribute("next");
	const int next = nextAttribute.as_int(0);

	auto const frames = new vector<const Frame*>();
	const auto frameNodes = node.children("frame");
	for (const xml_node frameNode : frameNodes) {
		auto const frame = deserializeFrame(frameNode);
		frames->push_back(frame);
	}

	return new Sequence(id, next, frames);
}

const Frame* Theme::deserializeFrame(const xml_node node) {
	const xml_attribute waitAttribute = node.attribute("wait");
	const int wait = waitAttribute.as_int(0);

	const xml_node imageReferenceNode = node.child("pic");
	const ImageReference* imageReference = deserializeImageReference(imageReferenceNode);

	return new Frame(wait, imageReference);
}

const ImageReference* Theme::deserializeImageReference(const xml_node node) {
	const xml_attribute idAttribute = node.attribute("id");
	const int id = idAttribute.as_int(0);

	const xml_attribute alphaAttribute = node.attribute("alpha");
	const int alpha = alphaAttribute.as_int(255);

	return new ImageReference(id, alpha);
}

} /* namespace theme */
} /* namespace desktop */
} /* namespace azriel */
} /* namespace im */

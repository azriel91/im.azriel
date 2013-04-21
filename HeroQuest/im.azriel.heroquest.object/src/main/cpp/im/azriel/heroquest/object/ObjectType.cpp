/*
 * Theme.cpp
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#include "im/azriel/heroquest/object/ObjectType.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace object {

#ifdef ENABLE_LOGGING
Logger* const ObjectType::LOGGER = Logger::getLogger("Theme::LOGGER");
#endif

ObjectType::~ObjectType() {
	delete this->header;

	for (auto sequence : *this->sequences) {
		delete sequence;
	}
	delete this->sequences;
}

const Header* ObjectType::getHeader() const {
	return this->header;
}

const int ObjectType::getId() const {
	return this->id;
}

const vector<const Sequence*>* ObjectType::getSequences() const {
	return this->sequences;
}

ObjectType::ObjectType(const int id, const Header* const header, const vector<const Sequence*>* const sequences) :
		id(id), header(header), sequences(sequences) {
}

const ObjectType* ObjectType::loadFromFile(const string path, const int objectTypeId) {
	xml_document doc;
	const xml_parse_result result = doc.load_file(path.c_str());
#ifdef ENABLE_LOGGING
	LOGGER->info("Loaded [%s]. Result: [%s]", path.c_str(), result.description());
#endif

	xml_node node = doc.root().child("object");

	const xml_node headerNode = node.child("header");
	const Header* header = deserializeHeader(headerNode);

	auto const sequences = new vector<const Sequence*>(1);
	auto sequenceNodes = node.children("sequence");
	for (const xml_node sequenceNode : sequenceNodes) {
		auto const sequence = deserializeSequence(sequenceNode);
		const int sequenceId = sequence->getId();
		auto size = sequences->size();

		// ensure sufficient capacity
		if (size <= (unsigned int) sequenceId) {
			const double val = log2((double) sequenceId);
			const int newSize = 2 << (int) (ceil(val));
			sequences->resize(newSize);
		}
		sequences->at(sequenceId) = sequence;
	}

	return new ObjectType(objectTypeId, header, sequences);
}

const Header* ObjectType::deserializeHeader(const xml_node node) {
	auto const imageMetadatas = new vector<const ImageMetadata*>();

	const auto nameNode = node.child("name");
	const string name(nameNode.text().as_string(""));

	const auto imageNodes = node.children("image");
	for (const xml_node imageNode : imageNodes) {
		auto const imageMetadata = deserializeImageMetadata(imageNode);
		imageMetadatas->push_back(imageMetadata);
	}

	return new Header(name, imageMetadatas);
}

const ImageMetadata* ObjectType::deserializeImageMetadata(const xml_node node) {
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

const Sequence* ObjectType::deserializeSequence(const xml_node node) {
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

const Frame* ObjectType::deserializeFrame(const xml_node node) {
	const xml_attribute waitAttribute = node.attribute("wait");
	const int wait = waitAttribute.as_int(0);

	const xml_node imageReferenceNode = node.child("pic");
	const ImageReference* imageReference = deserializeImageReference(imageReferenceNode);

	return new Frame(wait, imageReference);
}

const ImageReference* ObjectType::deserializeImageReference(const xml_node node) {
	const xml_attribute idAttribute = node.attribute("id");
	const int id = idAttribute.as_int(0);

	const xml_attribute alphaAttribute = node.attribute("alpha");
	const int alpha = alphaAttribute.as_int(255);

	return new ImageReference(id, alpha);
}

} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

/*
 * Theme.h
 *
 *  Created on: 20/02/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_OBJECT__OBJECTTYPE_H_
#define __IM_AZRIEL_HEROQUEST_OBJECT__OBJECTTYPE_H_

#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

#include "im/azriel/common/logger/Logger.h"
#include "im/azriel/heroquest/object/config/Header.h"
#include "im/azriel/heroquest/object/config/Frame.h"
#include "im/azriel/heroquest/object/config/ImageMetadata.h"
#include "im/azriel/heroquest/object/config/ImageReference.h"
#include "im/azriel/heroquest/object/config/Sequence.h"
#include "pugixml-1.2/pugixml.hpp"

using namespace std;
using namespace im::azriel::common::logger;
using namespace im::azriel::heroquest::object::config;
using namespace pugi;

namespace im {
namespace azriel {
namespace heroquest {
namespace object {

class ObjectType {
private:
	static constexpr int XML_SCHEMA_MISMATCH = 1000;
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif
	/**
	 * The id of this widget data.
	 */
	const int id;
	/**
	 * The header information for this widget.
	 */
	const Header* const header;
	/**
	 * The sequences defined for this widget.
	 */
	const vector<const Sequence*>* const sequences;

public:
	virtual ~ObjectType();
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
	const int getId() const;
	/**
	 * Get the sequences defined for this widget.
	 *
	 * @return the sequences
	 */
	const vector<const Sequence*>* getSequences() const;

private:
	ObjectType(const int id, const Header* const header, const vector<const Sequence*>* const sequences);

public:
	static const ObjectType* loadFromFile(const string path, const int objectTypeId);

private:
	static const Header* deserializeHeader(const xml_node node);
	static const ImageMetadata* deserializeImageMetadata(const xml_node node);
	static const Sequence* deserializeSequence(const xml_node node);
	static const Frame* deserializeFrame(const xml_node node);
	static const ImageReference* deserializeImageReference(const xml_node node);
};

} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_HEROQUEST_OBJECT__OBJECTTYPE_H_ */

/*
 * Logger.cpp
 *
 *  Created on: 27/05/2012
 *      Author: Azriel
 */

#include "im/azriel/common/logger/Logger.h"

namespace im {
namespace azriel {
namespace common {
namespace logger {

Logger* Logger::getLogger(string id) {
	static map<string, Logger*> loggersById;
	map<string, Logger*>::iterator it = loggersById.find(id);
	if (it == loggersById.end()) {
		Logger* logger = new Logger(id);
		loggersById.insert(pair<string, Logger*>(id, logger));
		return logger;
	}
	return it->second;
}

Logger::Logger(string id) {
	this->id = id;
}

void Logger::info(string format, ...) {
	printf("[INF] %-25s ", id.c_str());

	va_list argList;
	va_start(argList, format);
	vprintf(format.c_str(), argList);
	va_end(argList);

	printf("\n");
	fflush(stdout);
}

void Logger::debug(string format, ...) {
	printf("[DBG] %-25s ", id.c_str());

	va_list argList;
	va_start(argList, format);
	vprintf(format.c_str(), argList);
	va_end(argList);

	printf("\n");
	fflush(stdout);
}

void Logger::error(string format, ...) {
	fprintf(stderr, "[ERR] %-25s ", id.c_str());

	va_list argList;
	va_start(argList, format);
	vfprintf(stderr, format.c_str(), argList);
	va_end(argList);

	fprintf(stderr, "\n");
	fflush(stderr);
}

void Logger::warn(string format, ...) {
	printf("[WRN] %-25s ", id.c_str());

	va_list argList;
	va_start(argList, format);
	vprintf(format.c_str(), argList);
	va_end(argList);

	printf("\n");
	fflush(stdout);
}

} /* namespace logger */
} /* namespace common */
} /* namespace azriel */
} /* namespace im */

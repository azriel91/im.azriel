/*
 * Logger.h
 *
 *  Created on: 3/11/2012
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_COMMON_LOGGER__LOGGER_H_
#define __IM_AZRIEL_COMMON_LOGGER__LOGGER_H_

#include <cstdarg>
#include <cstdio>
#include <map>
#include <string>

using namespace std;

namespace im {
namespace azriel {
namespace common {
namespace logger {

class Logger {
private:
	string id;

public:
	static Logger* getLogger(string id);
	void debug(string format, ...);
	void error(string format, ...);
	void info(string format, ...);
	void warn(string format, ...);
private:
	Logger(string id);
	void operator=(Logger const&);
};

} /* namespace logger */
} /* namespace common */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_COMMON_LOGGER__LOGGER_H_ */

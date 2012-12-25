/*
 * Environment.h
 *
 *  Created on: 4/11/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_ENVIRONMENT__ENVIRONMENT_H_
#define __IM_AZRIEL_HEROQUEST_ENVIRONMENT__ENVIRONMENT_H_

#include "im/azriel/desktop/application/environment/Environment.h"
#include "im/azriel/heroquest/theme/Theme.h"

using namespace im::azriel::heroquest::theme;

namespace im {
namespace azriel {
namespace heroquest {
namespace environment {

class Environment: public im::azriel::desktop::application::environment::Environment {
protected:
	/**
	 * The current theme.
	 */
	const Theme* theme;
public:
	Environment(const int viewportWidth, const int viewportHeight, const int screenWidth, const int screenHeight,
			const Theme* const theme);
	virtual ~Environment();

	const Theme* getTheme() const;
	void setTheme(const Theme* const theme);
};

} /* namespace environment */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
#endif /* __IM_AZRIEL_HEROQUEST_ENVIRONMENT__ENVIRONMENT_H_ */

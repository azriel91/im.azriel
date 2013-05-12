/*
 * ApplicationConfiguration.h
 *
 *  Created on: 18/04/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_APPLICATION_CONFIG__APPLICATIONCONFIGURATION_H_
#define __IM_AZRIEL_HEROQUEST_APPLICATION_CONFIG__APPLICATIONCONFIGURATION_H_

#include <map>
#include <vector>
#include <string>

#include "im/azriel/common/job/Job.hpp"
#include "im/azriel/common/imports/SdlImports.h"
#include "im/azriel/heroquest/application/config/AssetConfiguration.h"
#include "im/azriel/heroquest/application/config/Reference.h"
#include "im/azriel/heroquest/object/ObjectType.h"

using namespace std;
using namespace im::azriel::common::job;
using namespace im::azriel::heroquest::object;

namespace im {
namespace azriel {
namespace heroquest {
namespace application {
namespace config {

class ApplicationConfiguration {
private:
	class ConfigLoadingJob: public Job<const ApplicationConfiguration*> {
	private:
		const AssetConfiguration* const assetConfiguration;

	public:
		ConfigLoadingJob(const AssetConfiguration* const assetConfiguration);
		virtual ~ConfigLoadingJob();

	protected:
		/**
		 * Method to be implemented by subclasses that is the actual implementation of the job.
		 *
		 * @return the return value for this job
		 */
		const ApplicationConfiguration* doWork();

	private:
		const map<const int, const ObjectType*>* loadObjectTypes(const vector<const Reference*>* const references);
	};

private:
#ifdef ENABLE_LOGGING
	/**
	 * The logger instance for this class.
	 */
	static Logger* const LOGGER;
#endif

private:
	const vector<const ObjectType*>* const objectTypes;
	const map<const int, const ObjectType*>* const objectTypeById;

public:
	virtual ~ApplicationConfiguration();

	const ObjectType* const getObjectType(const int id) const;
	const vector<const ObjectType*>* const getObjectTypes() const;

private:
	ApplicationConfiguration(const vector<const ObjectType*>* const objectTypes,
			const map<const int, const ObjectType*>* const objectTypeById);

public:
	static const ApplicationConfiguration* loadApplicationConfiguration(const AssetConfiguration* const assetConfiguration);
	static Job<const ApplicationConfiguration*>* loadApplicationConfigurationAsJob(
			const AssetConfiguration* const assetConfiguration);

private:
	static const map<const int, const ObjectType*>* loadObjectTypes(const vector<const Reference*>* const references);
	static const vector<const ObjectType*>* extractObjectTypes(
			const map<const int, const ObjectType*>* const objectTypeById);
};

} /* namespace config */
} /* namespace application */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_HEROQUEST_APPLICATION_CONFIG__APPLICATIONCONFIGURATION_H_ */

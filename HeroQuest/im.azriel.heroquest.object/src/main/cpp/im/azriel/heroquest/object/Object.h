/*
 * Actor.h
 *
 *  Created on: 13/04/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_OBJECT__OBJECT_H_
#define __IM_AZRIEL_HEROQUEST_OBJECT__OBJECT_H_

namespace im {
namespace azriel {
namespace heroquest {
namespace object {

/**
 * An Object instance represents an in-game object, whether it is a player's character, a weapon, a ride, or projectile.
 */
class Object {
protected:
	/**
	 * The in-game id of this object.
	 */
	const int id;
	double x;
	double y;
	double z;

public:
	Object(const int id);
	virtual ~Object();
};

} /* namespace object */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_HEROQUEST_OBJECT__OBJECT_H_ */

/**
 * @file contactListener.h
 *
 * @brief The contactListener header file.
 */

#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <iostream>

#include "b2entity.h"

#include <Box2D/Box2D.h>

/**
 * @brief The ContactListener class takes care of sending all the right collision to all of the B2Entity's
 */
class ContactListener : public b2ContactListener{
public:
	///< @brief Constructor of the ContactListener
	ContactListener();
	///< @brief Destructor of the ContactListener
	~ContactListener();

	/// @brief Whenever a collision happens between two B2Entity(fixtures) both of the B2Entity's will be send the contact information of the other B2Entity
	/// @param contact You will get this b2Contact* by the b2World. NOTE don't forget to set the contactListener for example: world->SetContactListener(contactListener);
	/// @return void
	void BeginContact(b2Contact* contact);
	/// @brief Whenever a collision stop between b2Entity(fixtures) both of the B2Entity's will be removed from from each other
	/// @param contact You will get this b2Contact* by the b2World. NOTE don't forget to set the contactListener for example: world->SetContactListener(contactListener);
	/// @return void
	void EndContact(b2Contact* contact);
private:

};

#endif // !CONTACTLISTENER_H

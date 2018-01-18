/**
 * @file contactListener.h
 *
 * @brief The ContactListener header file.
 */

#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "b2entity.h"

/**
 * @brief The ContactListener class
 */
class ContactListener : public b2ContactListener{
public:
	/// @brief Constructor of the ContactListener
	ContactListener();
	/// @brief Destructor of the ContactListener
	virtual ~ContactListener();

	/// @brief BeginContact whenever a collision happens between two B2Entity(fixtures) both of the B2Entity's will be send the contact information of the other B2Entity
	/// @param contact You will get this b2Contact* by the b2World. NOTE don't forget to set the contactListener for example: world->SetContactListener(contactListener);
	/// @return void
	void BeginContact(b2Contact* contact);
	/// @brief EndContact whenever a collision stop between b2Entity(fixtures) both of the B2Entity's will be removed from from each other
	/// @param contact You will get this b2Contact* by the b2World. NOTE don't forget to set the contactListener for example: world->SetContactListener(contactListener);
	/// @return void
	void EndContact(b2Contact* contact);
private:

};

#endif // !CONTACTLISTENER_H

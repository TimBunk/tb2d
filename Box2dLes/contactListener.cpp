#include "contactListener.h"

ContactListener::ContactListener() {

}

ContactListener::~ContactListener() {

}

void ContactListener::BeginContact(b2Contact* contact) {
	b2Fixture* fa = contact->GetFixtureA();
	b2Fixture* fb = contact->GetFixtureB();

	// Check if the received data is null and check if it is a B2Entity otherwise return
	if (fa == NULL || fb == NULL) { return; }
	if (fa->GetUserData() == NULL || fb->GetUserData() == NULL) { return; }
	if (static_cast<B2Entity*>(fa->GetUserData()) == NULL || static_cast<B2Entity*>(fb->GetUserData()) == NULL) { return; }
	// Add the contacts to the b2entity
	static_cast<B2Entity*>(fa->GetUserData())->AddContact(static_cast<B2Entity*>(fb->GetUserData()));
	static_cast<B2Entity*>(fb->GetUserData())->AddContact(static_cast<B2Entity*>(fa->GetUserData()));
}

void ContactListener::EndContact(b2Contact* contact) {
	b2Fixture* fa = contact->GetFixtureA();
	b2Fixture* fb = contact->GetFixtureB();

	// Check if the received data is null and check if it is a B2Entity otherwise return
	if (fa == NULL || fb == NULL) { return; }
	if (fa->GetUserData() == NULL || fb->GetUserData() == NULL) { return; }
	if (static_cast<B2Entity*>(fa->GetUserData()) == NULL || static_cast<B2Entity*>(fb->GetUserData()) == NULL) { return; }
	// remove the contacts from the b2entity
	static_cast<B2Entity*>(fa->GetUserData())->RemoveContact(static_cast<B2Entity*>(fb->GetUserData()));
	static_cast<B2Entity*>(fb->GetUserData())->RemoveContact(static_cast<B2Entity*>(fa->GetUserData()));
}

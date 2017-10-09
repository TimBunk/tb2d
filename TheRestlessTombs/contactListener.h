#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <iostream>

#include "b2entity.h"

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener{
public:
	ContactListener();
	~ContactListener();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
private:

};

#endif // !CONTACTLISTENER_H

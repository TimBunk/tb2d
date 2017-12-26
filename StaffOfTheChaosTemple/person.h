#ifndef PERSON_H
#define PERSON_H

#include "box2Dclasses/b2entity.h"

class Person : public B2Entity
{
public:
	Person(int health, float speed, int damage, int width, int height, unsigned int textureID, b2World * world);
	~Person();

	void Damage(int damage);
	bool IsAlive();

protected:
	int health;
	float speed;
	int damage;

private:

};

#endif // !PERSON_H

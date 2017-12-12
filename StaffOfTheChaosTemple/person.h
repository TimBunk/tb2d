#ifndef PERSON_H
#define PERSON_H

#include "b2entity.h"

class Person : public B2Entity
{
public:
	Person(int health, float speed, int damage, int width, int height, Texture* texture, Camera * camera, b2World * world);
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

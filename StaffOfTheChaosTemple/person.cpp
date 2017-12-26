#include "person.h"

Person::Person(int health, float speed, int damage, int width, int height, unsigned int textureID, b2World * world) : B2Entity::B2Entity(width, height, textureID, world)
{
	this->health = health;
	this->speed = speed;
	this->damage = damage;
}

Person::~Person()
{
}

void Person::Damage(int damage)
{
	if (health - damage > 0) {
		health -= damage;
	}
	else {
		health = 0;
	}
}

bool Person::IsAlive()
{
	if (health > 0) {
		return true;
	}
	return false;
}

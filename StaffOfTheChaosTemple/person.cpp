#include "person.h"

Person::Person(int health, float speed, int damage, int width, int height, Texture* texture, Camera * camera, b2World * world) : B2Entity::B2Entity(width, height, glm::vec2(0,0), texture, camera, world)
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

#include "person.h"

Person::Person(float health, float speed, float damage, int width, int height, unsigned int textureID, b2World * world) : Linkable::Linkable(width, height, textureID, world)
{
	this->currentHealth = health;
	this->maxHealth = health;
	this->speed = speed;
	this->damage = damage;
}

Person::~Person()
{
}

void Person::Damage(float damage)
{
	if (currentHealth - damage > 0.0f) {
		currentHealth -= damage;
	}
	else {
		currentHealth = 0.0f;
		enabled = true;
	}
}

bool Person::IsAlive()
{
	if (currentHealth > 0.0f) {
		return true;
	}
	return false;
}
#ifndef PERSON_H
#define PERSON_H

#include "b2entity.h"
#include "linkable.h"

class Person : public Linkable
{
public:
	Person(float health, float speed, float damage, int width, int height, unsigned int textureID, b2World * world);
	~Person();

	void Damage(float damage);
	bool IsAlive();

	void SetMaxHealth(float value) { this->maxHealth = value; }
	void SetDamage(float value) { this->damage = value; }
	void SetSpeed(float value) { this->speed = value; }

	float GetCurrentHealth() { return currentHealth; };
	float GetMaxHealth() { return maxHealth; };
	float GetSpeed() { return speed; };
	float GetDamage() { return damage; };

protected:
	float maxHealth;
	float currentHealth;
	float speed;
	float damage;

private:

};

#endif // !PERSON_H

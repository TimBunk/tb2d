#ifndef DAMAGEPOTION_H
#define DAMAGEPOTION_H

#include "potion.h"

struct DamageBoost {
	int value = 1;
	float lifeTime = 0.0f;
	bool active = false;
};

class DamagePotion : public Potion {
public:
	DamagePotion(int damageBoost, float lifeTime, Camera* camera, Shader* shader);
	~DamagePotion();

	DamageBoost Use();
private:
	int damageBoost;
	float lifeTime;
};

#endif // !DAMAGEPOTION_H

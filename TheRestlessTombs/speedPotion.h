#ifndef SPEEDPOTION_H
#define SPEEDPOTION_H

#include "potion.h"

struct SpeedBoost {
	float movemementSpeed = 0.0f;
	float attackSpeed = 0.0f;
	float lifeTime = 0.0f;
	bool active = false;
};

class SpeedPotion : public Potion {
public:
	SpeedPotion(float speedBoost, float attackSpeedBoost, float lifeTime, Camera* camera, Shader* shader, b2World* world);
	~SpeedPotion();

	SpeedBoost Use();
private:
	float movementSpeed;
	float attackSpeed;
	float lifeTime;
};

#endif // !SPEEDPOTION_H

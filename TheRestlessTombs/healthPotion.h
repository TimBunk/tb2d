#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include "potion.h"
#include "player.h"

class HealthPotion : public Potion {
public:
	HealthPotion(int healing, Camera* camera, Shader* shader);
	~HealthPotion();

	float Use();
private:
	int healing;
};

#endif // !HEALTHPOTION_H

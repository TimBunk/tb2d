#ifndef PSYCHOORC_H
#define PSYCHOORC_H

#include "enemy.h"

class PsychoOrc : public Enemy {
public:
	PsychoOrc(Player* player, float lineOfSight, Texture _sword, Camera* camera, Shader* shader, Shader* lineRenderer, b2World* world);
	~PsychoOrc();

	void Update(float deltaTime);
	void TakeDamage(int damage);
	void Reset();
private:
	Weapon* sword;
};

#endif //!PSYCHOORC_H

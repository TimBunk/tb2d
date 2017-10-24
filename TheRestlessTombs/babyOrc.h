#ifndef BABYORC_H
#define BABYORC_H

#include "enemy.h"
#include "weapon.h"

class BabyOrc : public Enemy {
public:
	BabyOrc(Player* player, float lineOfSight, Texture _sword, Camera* camera, Shader* shader, Shader* lineRenderer, b2World* world);
	~BabyOrc();

	void Update(float deltaTime);
	void TakeDamage(int damage);
	void Reset();
private:
	Weapon* sword;
};

#endif // !BABYORC_H

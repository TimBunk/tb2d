#ifndef PSYCHOORC_H
#define PSYCHOORC_H

#include "enemy.h"

class PsychoOrc : public Enemy {
public:
	PsychoOrc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~PsychoOrc();

	void Update(double deltaTime);
	void TakeDamage(int damage);
	void Reset();
private:
	Weapon* sword;
};

#endif //!PSYCHOORC_H

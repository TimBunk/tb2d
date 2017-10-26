#ifndef ARMOREDORC_H
#define ARMOREDORC_H

#include "enemy.h"

class ArmoredOrc : public Enemy {
public:
	ArmoredOrc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~ArmoredOrc();

	void Update(float deltaTime);
	void TakeDamage(int damage);
	void Reset();
private:
	Weapon* sword;
};

#endif //!ARMOREDORC_H

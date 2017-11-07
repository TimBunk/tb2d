#ifndef ORC_H
#define ORC_H

#include "enemy.h"

class Orc : public Enemy {
public:
	Orc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~Orc();

	void Update(double deltaTime);
	void TakeDamage(int damage);
	void Reset();
private:
	Weapon* sword;
};

#endif // ORC_H

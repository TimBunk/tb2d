#ifndef ORC_H
#define ORC_H

#include "enemy.h"

class Orc : public Enemy {
public:
	Orc(Player* player, float lineOfSight, Texture _sword, Camera* camera, Shader* shader, Shader* lineRenderer, b2World* world);
	~Orc();

	void Update(float deltaTime);
	void TakeDamage(int damage);
	void Reset();
private:
	Weapon* sword;
};

#endif // ORC_H

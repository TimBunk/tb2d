#ifndef BOMBERORC_H
#define BOMBERORC_H

#include "enemy.h"
#include "bomb.h"

class BomberOrc : public Enemy {
public:
	BomberOrc(ResourceManager* rm, Player* player, float lineOfSight, Camera* camera, Shader* shader, Shader* lineRenderer, b2World* world);
	~BomberOrc();

	void Update(float deltaTime);
	bool LookForPlayer(float deltaTime);
	void TakeDamage(int damage);
	void Reset();
private:
	ResourceManager* rm;
	float timer;
	std::vector<Bomb*> bombs;
};


#endif //!BOMBERORC_H

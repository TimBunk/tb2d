#ifndef BOMBERORC_H
#define BOMBERORC_H

#include "enemy.h"
#include "bomb.h"

class BomberOrc : public Enemy {
public:
	BomberOrc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~BomberOrc();

	void Update(double deltaTime);
	bool LookForPlayer(float deltaTime);
	void TakeDamage(int damage);
	void Reset();
private:
	ResourceManager* rm;
	float timer;
	std::vector<Bomb*> bombs;
};


#endif //!BOMBERORC_H

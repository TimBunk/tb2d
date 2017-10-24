#ifndef NECROMANCERORC_H
#define NECROMANCERORC_H

#include "babyOrc.h"

class NecromancerOrc : public Enemy {
public:
	NecromancerOrc(float spawnCooldown, ResourceManager* rm, Player* player, float lineOfSight, Camera* camera, Shader* shader, Shader* lineRenderer, b2World* world);
	~NecromancerOrc();

	void Update(float deltaTime);
	void TakeDamage(int damage);
	void Reset();

	void CreateBody(int x, int y, int w, int h);
private:
	float spawnCooldown;
	float currentCooldown;

	Entity* babyOrcsHolder;
	std::vector<BabyOrc*> babyOrcs;

	ResourceManager* rm;
};

#endif //!NECROMANCERORC_H

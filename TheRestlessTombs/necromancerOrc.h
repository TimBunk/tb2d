#ifndef NECROMANCERORC_H
#define NECROMANCERORC_H

#include "babyOrc.h"

class NecromancerOrc : public Enemy {
public:
	NecromancerOrc(float spawnCooldown, Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~NecromancerOrc();

	void Update(float deltaTime);
	void TakeDamage(int damage);
	void Reset();

	void CreateBody(int x, int y, int w, int h);
	void SetActive(bool active);
private:
	float spawnCooldown;
	float currentCooldown;

	Entity* babyOrcsHolder;
	std::vector<BabyOrc*> babyOrcs;
};

#endif //!NECROMANCERORC_H

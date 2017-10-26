#ifndef BOSSORC_H
#define BOSSORC_H

#include "boss.h"

class BossOrc : public Boss {
public:
	BossOrc(std::string nameBoss, ResourceManager* rm, Player* player, float lineOfSight, Camera* camera, Shader* shader, Shader* lineRenderer, b2World* world);
	~BossOrc();

	void Update(float deltaTime);
	bool LookForPlayer(float deltaTime);
	void TakeDamage(int damage);
	void Reset();
private:
	Weapon* hammer;
	float timer;
	float specialAbilityCooldown;
	float specialAbilityTimer;
	float specialAbilityDuration;
	bool specialAbility;
	b2Vec2 specialAttackDirection;
	float originalSpeed;
};

#endif //!BOSSORC_H

#ifndef BOSSORC_H
#define BOSSORC_H

#include "boss.h"

class BossOrc : public Boss {
public:
	BossOrc(std::string nameBoss, Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~BossOrc();

	void Update(double deltaTime);
	bool LookForPlayer(double deltaTime);
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

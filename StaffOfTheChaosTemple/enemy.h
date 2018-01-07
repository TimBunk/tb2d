#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "box2Dclasses/raycast.h"
#include "mirror.h"

class Enemy : public Person
{
public:
	Enemy(Player* player, float lineOfSight, float forceTowardsPlayer, float forceFromAbstacles, float health, float speed, float damage, int width, int height, unsigned int textureID, b2World * world);
	~Enemy();

	void Update(double deltaTime);
	void Die();

	float GetLineOfSight() { return lineOfSight; }
	void SetLineOfSight(float lineOfSight) { this->lineOfSight = lineOfSight; }

private:
	bool dead;
	Sprite* redHealthbar;
	Sprite* greenHealthbar;

	Mirror* mirror;
	float lineOfSight;
	float attackRadius;
	B2Entity* sword;

	Player* player;
	glm::vec2 lastPositionPlayer;
	glm::vec2 velocity;
	float forceTowardsPlayer;
	float forceFromObstacles;
	B2Entity* distanceObjects;
	Raycast* raycast;
};

#endif // !ENEMY_H

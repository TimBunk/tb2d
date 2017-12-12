#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "raycastCallBack.h"

class Enemy : public Person
{
public:
	Enemy(Player* player, float lineOfSight, float forceTowardsPlayer, float forceFromAbstacles, int health, float speed, int damage, Camera * camera, b2World * world);
	~Enemy();

	void Update(double deltaTime);

private:
	float lineOfSight;
	Player* player;
	glm::vec2 lastPositionPlayer;
	glm::vec2 velocity;
	float forceTowardsPlayer;
	float forceFromObstacles;
	B2Entity* distanceObjects;
	RaycastCallBack* raycast;
};

#endif // !ENEMY_H

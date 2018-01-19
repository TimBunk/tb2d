#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "raycast.h"
#include "mirror.h"

class Enemy : public Person
{
public:
	Enemy(Player* player, float lineOfSight, float forceTowardsPlayer, float forceFromAbstacles, float health, float speed, float damage, int width, int height, unsigned int textureID, b2World * world);
	~Enemy();

	void Init();

	void Update(double deltaTime);
	void Draw();

	float GetLineOfSight() { return lineOfSight; }
	void SetLineOfSight(float lineOfSight) { this->lineOfSight = lineOfSight; }
	
	void SetPlayer(Player* player) { this->player = player; }

private:
	Sprite* redHealthbar;
	Sprite* greenHealthbar;

	//Mirror* mirror;
	float lineOfSight;
	float attackRadius;
	B2Entity* sword;

	Player* player;
	glm::vec2 lastPositionPlayer;
	glm::vec2 velocity;
	float forceTowardsPlayer;
	float forceFromObstacles; // If the enemy walks against a wall then a force will be applied to the enemy pushing him away from the wall
	// Distance objects if for checking whenever something is in the radius of this enemy and push the enemy with a force away from it
	B2Entity* distanceObjects;
	Raycast* raycast;
};

#endif // !ENEMY_H
